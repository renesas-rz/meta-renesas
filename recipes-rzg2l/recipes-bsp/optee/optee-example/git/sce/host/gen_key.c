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

#define KEY_BUFFER_SIZE     (2000)

#define KEY_GEN_PAIR        (1)
#define KEY_GEN_CMMN        (0)

struct key_info {
    char *key_opt;
    uint32_t cmd;
    uint32_t pair;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    uint32_t cmd;
    uint32_t pair;
    char *wuk1_file;
    char *wuk2_file;
};

extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct key_info key_list[] = {
    {"aes128",    PTA_CMD_AES128_WrappedKeyGenerate,                  KEY_GEN_CMMN},
    {"aes256",    PTA_CMD_AES256_WrappedKeyGenerate,                  KEY_GEN_CMMN},
    {"rsa1024",   PTA_CMD_RSA1024_WrappedKeyPairGenerate,             KEY_GEN_PAIR},
    {"rsa2048",   PTA_CMD_RSA2048_WrappedKeyPairGenerate,             KEY_GEN_PAIR},
    {"nistp192",  PTA_CMD_ECC_secp192r1_WrappedKeyPairGenerate,       KEY_GEN_PAIR},
    {"nistp224",  PTA_CMD_ECC_secp224r1_WrappedKeyPairGenerate,       KEY_GEN_PAIR},
    {"nistp256",  PTA_CMD_ECC_secp256r1_WrappedKeyPairGenerate,       KEY_GEN_PAIR},
    {"bsip512r1", PTA_CMD_ECC_BrainpoolP512r1_WrappedKeyPairGenerate, KEY_GEN_PAIR},
    {},
};

static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "Common Key Generation\n");
    fprintf(stderr, "Usage: %s -k [-t <Type>] <Key1> \n", program);
    fprintf(stderr, "\t-t <Type>        Generation Key Type. \n");
    fprintf(stderr, "\t                 Use default \"aes128\" if not set.\n");
    fprintf(stderr, "\t                 - \"aes128\", \"aes256\" \n");
    fprintf(stderr, "\t<Key1>           File name of the wrapped common key to be output.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Pair Key Generation\n");
    fprintf(stderr, "Usage: %s -k [-t <Type>] <Key1> <Key2> \n", program);
    fprintf(stderr, "\t-t <Type>        Generation Key Type. \n");
    fprintf(stderr, "\t                 - \"rsa1024\",  \"rsa2048\" \n");
    fprintf(stderr, "\t                 - \"nistp192\", \"nistp224\", \"nistp256\" \n");
    fprintf(stderr, "\t                 - \"bsip512r1\" \n");
    fprintf(stderr, "\t<Key1>           File name of the wrapped private key to be output.\n");
    fprintf(stderr, "\t<Key2>           File name of the wrapped public key to be output.\n");
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

    if ((optind + 1) > argc) {
        fprintf(stderr, "Cannot find the <Key1>. \n");
        usage(argv[0]);
    }
    if ((info->pair) && ((optind + 2) > argc)) {
        fprintf(stderr, "Cannot find the <Key2>. \n");
        usage(argv[0]);
    }

    ctx->cmd       = info->cmd;
    ctx->pair      = info->pair;
    ctx->wuk1_file = argv[optind];
    ctx->wuk2_file = ctx->pair ? argv[optind + 1] : NULL;
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

static int generate_key(struct sample_ctx *ctx, uint32_t *wuk, uint32_t *wuk_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = wuk;
    op.params[0].tmpref.size = *wuk_sz;
    
    res = TEEC_InvokeCommand(&ctx->sess, ctx->cmd, &op, &origin);
    if (res != TEEC_SUCCESS){
        fprintf(stderr, "TEEC_InvokeCommand(GENERATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *wuk_sz = op.params[0].tmpref.size;
    return 0;
}

static int save_generated_key1(struct sample_ctx *ctx, uint32_t *wuk)
{
    void *wuk1;
    uint32_t wuk1_sz;
    
    switch (ctx->cmd)
    {
    case PTA_CMD_AES128_WrappedKeyGenerate:
        wuk1 = wuk;
        wuk1_sz = sizeof(sce_aes_wrapped_key_t);
        break;
    case PTA_CMD_AES256_WrappedKeyGenerate:
        wuk1 = wuk;
        wuk1_sz = sizeof(sce_aes_wrapped_key_t);
        break;
    case PTA_CMD_RSA1024_WrappedKeyPairGenerate:
        wuk1 = &((sce_rsa1024_wrapped_pair_key_t *)wuk)->priv_key;
        wuk1_sz = sizeof(sce_rsa1024_private_wrapped_key_t);
        break;
    case PTA_CMD_RSA2048_WrappedKeyPairGenerate:
        wuk1 = &((sce_rsa2048_wrapped_pair_key_t *)wuk)->priv_key;
        wuk1_sz = sizeof(sce_rsa2048_private_wrapped_key_t);
        break;
    case PTA_CMD_ECC_secp192r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_secp224r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_secp256r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_BrainpoolP512r1_WrappedKeyPairGenerate:
        wuk1 = &((sce_ecc_wrapped_pair_key_t *)wuk)->priv_key;
        wuk1_sz = sizeof(sce_ecc_private_wrapped_key_t);
        break;
    default:
        fprintf(stderr, "The code to save the wrapped key is not implemented.");
        return -1;
    }

    printf("Save the generated key to file \"%s\"\n", ctx->wuk1_file);
    return save_file(ctx->wuk1_file, wuk1, wuk1_sz);
}

static int save_generated_key2(struct sample_ctx *ctx, uint32_t *wuk)
{
    void *wuk2;
    uint32_t wuk2_sz;

    switch (ctx->cmd)
    {
    case PTA_CMD_AES128_WrappedKeyGenerate:
    case PTA_CMD_AES256_WrappedKeyGenerate:
        return 0;
    case PTA_CMD_RSA1024_WrappedKeyPairGenerate:
        wuk2 = &((sce_rsa1024_wrapped_pair_key_t *)wuk)->pub_key;
        wuk2_sz = sizeof(sce_rsa1024_public_wrapped_key_t);
        break;
    case PTA_CMD_RSA2048_WrappedKeyPairGenerate:
        wuk2 = &((sce_rsa2048_wrapped_pair_key_t *)wuk)->pub_key;
        wuk2_sz = sizeof(sce_rsa2048_public_wrapped_key_t);
        break;
    case PTA_CMD_ECC_secp192r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_secp224r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_secp256r1_WrappedKeyPairGenerate:
    case PTA_CMD_ECC_BrainpoolP512r1_WrappedKeyPairGenerate:
        wuk2 = &((sce_ecc_wrapped_pair_key_t *)wuk)->pub_key;
        wuk2_sz = sizeof(sce_ecc_public_wrapped_key_t);
        break;
    default:
        fprintf(stderr, "The code to save the wrapped key is not implemented.");
        return -1;
    }

    printf("Save the generated key to file \"%s\"\n", ctx->wuk2_file);
    return save_file(ctx->wuk2_file, wuk2, wuk2_sz);
}

int gen_key_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;
    
    uint32_t wuk_size = sizeof(wuk_buff);

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if(res)
        goto err;

    printf("Generate the wrapped key with the TA\n");
    res = generate_key(&ctx, wuk_buff, &wuk_size);
    if(res)
        goto err;

    res = save_generated_key1(&ctx, wuk_buff);
    if(res)
        goto err;

    res = save_generated_key2(&ctx, wuk_buff);
    if(res)
        goto err;

err:
    terminate_tee_session(&ctx);
    return 0;
}
