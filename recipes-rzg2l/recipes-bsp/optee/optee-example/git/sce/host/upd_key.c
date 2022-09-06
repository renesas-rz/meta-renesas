// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022, Renesas Electronics
 */

#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* For the UUID (found in the TA's h-file(s)) */
#include <pta_sce.h>

#define KEY_BUFFER_SIZE     (1000)

struct key_info {
    char *   key_opt;
    uint32_t cmd;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    sce_key_update_key_t kuk;
    uint32_t cmd;
    char *euk_file;
    char *wuk_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);
extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct key_info key_list[] = {
    {"aes128",       PTA_CMD_AES128_EncryptedKeyWrap},
    {"aes256",       PTA_CMD_AES256_EncryptedKeyWrap},
    {"rsa1024pub",   PTA_CMD_RSA1024_EncryptedPublicKeyWrap},
    {"rsa1024pri",   PTA_CMD_RSA1024_EncryptedPrivateKeyWrap},
    {"rsa2048pub",   PTA_CMD_RSA2048_EncryptedPublicKeyWrap},
    {"rsa2048pri",   PTA_CMD_RSA2048_EncryptedPrivateKeyWrap},
    {"rsa4096pub",   PTA_CMD_RSA4096_EncryptedPublicKeyWrap},
    {"nistp192pub",  PTA_CMD_ECC_secp192r1_EncryptedPublicKeyWrap},
    {"nistp192pri",  PTA_CMD_ECC_secp192r1_EncryptedPrivateKeyWrap},
    {"nistp224pub",  PTA_CMD_ECC_secp224r1_EncryptedPublicKeyWrap},
    {"nistp224pri",  PTA_CMD_ECC_secp224r1_EncryptedPrivateKeyWrap},
    {"nistp256pub",  PTA_CMD_ECC_secp256r1_EncryptedPublicKeyWrap},
    {"nistp256pri",  PTA_CMD_ECC_secp256r1_EncryptedPrivateKeyWrap},
    {"bsip512r1pub", PTA_CMD_ECC_BrainpoolP512r1_EncryptedPublicKeyWrap},
    {"bsip512r1pri", PTA_CMD_ECC_BrainpoolP512r1_EncryptedPrivateKeyWrap},
    {},
};

static uint32_t kuk_buff [16] = {
#error "Write the Wrapped Key Update Key here."
};

static uint32_t iv0_buff[4] = {
#error "Write the initialization vector for key update here."
};

static uint32_t euk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "User Key Update\n");
    fprintf(stderr, "Usage: %s -u [-t <Type>] <E_KEY> <W_KEY>\n", program);
    fprintf(stderr, "\t-t <Type>        update Key Type. \n");
    fprintf(stderr, "\t                 Use default \"aes128\" if not set.\n");
    fprintf(stderr, "\t                 - \"aes128\",       \"aes256\" \n");
    fprintf(stderr, "\t                 - \"rsa1024pub\",   \"rsa1024pri\" \n");
    fprintf(stderr, "\t                 - \"rsa2048pub\",   \"rsa2048pri\" \n");
    fprintf(stderr, "\t                 - \"rsa4096pub\" \n");
    fprintf(stderr, "\t                 - \"nistp192pub\",  \"nistp192pri\" \n");
    fprintf(stderr, "\t                 - \"nistp224pub\",  \"nistp224pri\" \n");
    fprintf(stderr, "\t                 - \"nistp256pub\",  \"nistp256pri\" \n");
    fprintf(stderr, "\t                 - \"bsip512r1pub\", \"bsip512r1pri\" \n");
    fprintf(stderr, "\t<E_KEY>          File name of the encrypted user key to input. \n");
    fprintf(stderr, "\t<W_KEY>          File name of the wrapped user key to be output. \n");
    fprintf(stderr, "\n");
	exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *key_opt = "aes128";
    struct key_info *info = NULL;

    while (-1 != (opt = getopt(argc, argv, "t:h"))) {      
        switch (opt) {
        case 't':
            key_opt = optarg;
            break;
        case 'h':
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    for (int i = 0; NULL != key_list[i].key_opt; i++) {
        if (!strcasecmp(key_opt, key_list[i].key_opt)) {
            info = &key_list[i];
            break;
        }
    }
    if (NULL == info) {
        fprintf(stderr, "Bad <Type> \"%s\" \n", key_opt);
        usage(argv[0]);
    }

    if ((optind + 2) > argc) {
        fprintf(stderr, "Cannot find the <E_KEY> or <W_KEY> \n");
        usage(argv[0]);
    }
    
    ctx->cmd      = info->cmd;
    ctx->euk_file = argv[optind];
    ctx->wuk_file = argv[optind + 1];
}

static int prepare_tee_session(struct sample_ctx *ctx)
{
    TEEC_UUID uuid = PTA_SCE_UUID;
    uint32_t origin;
    TEEC_Result res;

    /* Initialize a context connecting us to the TEE */
    res = TEEC_InitializeContext(NULL, &ctx->ctx);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InitializeContext failed with code 0x%x", res);
        return -1;
    }

    /* Open a session with the TA */
    res = TEEC_OpenSession(&ctx->ctx, &ctx->sess, &uuid,
                   TEEC_LOGIN_PUBLIC, NULL, NULL, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_Opensession failed with code 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static void terminate_tee_session(struct sample_ctx *ctx)
{
    TEEC_CloseSession(&ctx->sess);
    TEEC_FinalizeContext(&ctx->ctx);
}

static int update_encrypted_user_key(struct sample_ctx *ctx, uint32_t *euk, uint32_t euk_sz, 
    uint32_t *wuk, uint32_t * wuk_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT, 
        TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INOUT);

    memcpy((ctx->kuk).value, kuk_buff, sizeof((ctx->kuk).value));
    
    op.params[0].tmpref.buffer = iv0_buff;
    op.params[0].tmpref.size = sizeof(iv0_buff);
    op.params[1].tmpref.buffer = euk;
    op.params[1].tmpref.size = euk_sz;
    op.params[2].tmpref.buffer = &ctx->kuk;
    op.params[2].tmpref.size = sizeof(ctx->kuk);
    op.params[3].tmpref.buffer = wuk;
    op.params[3].tmpref.size = *wuk_sz;
    
    res = TEEC_InvokeCommand(&ctx->sess, ctx->cmd, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(UPDATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *wuk_sz = op.params[3].tmpref.size;
    return 0;
}

int upd_key_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;
    
    uint32_t euk_size = sizeof(euk_buff);
    uint32_t wuk_size = sizeof(wuk_buff);

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if(res)
        goto err;
    
    printf("Load the encrypted user key \"%s\"\n", ctx.euk_file);
    res = load_file(ctx.euk_file, euk_buff, &euk_size);
    if(res)
        goto err;

    printf("Update the encrypted user key with the TA\n");
    res = update_encrypted_user_key(&ctx, euk_buff, euk_size, wuk_buff, &wuk_size);
    if(res)
        goto err;

    printf("Save the new key to file \"%s\"\n", ctx.wuk_file);
    res = save_file(ctx.wuk_file, wuk_buff, wuk_size);
    if(res)
        goto err;

err:
    terminate_tee_session(&ctx);
    return 0;
}
