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
#include <pta_sce_aes.h>

#define AES_BLOCK_SIZE      (HW_SCE_AES_BLOCK_BYTE_SIZE)
#define KEY_BUFFER_SIZE     (sizeof(sce_aes_wrapped_key_t))
#define DAT_BUFFER_SIZE     (AES_BLOCK_SIZE * 16)

#define AES_ENC_MODE        (1)
#define AES_DEC_MODE        (0)

struct aes_info {
    char *aes_opt;
    uint32_t init;
    uint32_t update;
    uint32_t final;
    uint32_t mode;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    sce_aes_handle_t aes;
    uint32_t init;
    uint32_t update;
    uint32_t final;
    uint32_t mode;
    char *inp_file;
    char *out_file;
    char *wuk_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);
extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct aes_info aes_list[] = {
    {"aes128ecb_enc", PTA_CMD_AES128ECB_EncryptInit, PTA_CMD_AES128ECB_EncryptUpdate, PTA_CMD_AES128ECB_EncryptFinal, AES_ENC_MODE},
    {"aes128ecb_dec", PTA_CMD_AES128ECB_DecryptInit, PTA_CMD_AES128ECB_DecryptUpdate, PTA_CMD_AES128ECB_DecryptFinal, AES_DEC_MODE},
    {"aes256ecb_enc", PTA_CMD_AES256ECB_EncryptInit, PTA_CMD_AES256ECB_EncryptUpdate, PTA_CMD_AES256ECB_EncryptFinal, AES_ENC_MODE},
    {"aes256ecb_dec", PTA_CMD_AES256ECB_DecryptInit, PTA_CMD_AES256ECB_DecryptUpdate, PTA_CMD_AES256ECB_DecryptFinal, AES_DEC_MODE},
    {"aes128cbc_enc", PTA_CMD_AES128CBC_EncryptInit, PTA_CMD_AES128CBC_EncryptUpdate, PTA_CMD_AES128CBC_EncryptFinal, AES_ENC_MODE},
    {"aes128cbc_dec", PTA_CMD_AES128CBC_DecryptInit, PTA_CMD_AES128CBC_DecryptUpdate, PTA_CMD_AES128CBC_DecryptFinal, AES_DEC_MODE},
    {"aes256cbc_enc", PTA_CMD_AES256CBC_EncryptInit, PTA_CMD_AES256CBC_EncryptUpdate, PTA_CMD_AES256CBC_EncryptFinal, AES_ENC_MODE},
    {"aes256cbc_dec", PTA_CMD_AES256CBC_DecryptInit, PTA_CMD_AES256CBC_DecryptUpdate, PTA_CMD_AES256CBC_DecryptFinal, AES_DEC_MODE},
    {"aes128ctr_enc", PTA_CMD_AES128CTR_EncryptInit, PTA_CMD_AES128CTR_EncryptUpdate, PTA_CMD_AES128CTR_EncryptFinal, AES_ENC_MODE},
    {"aes128ctr_dec", PTA_CMD_AES128CTR_DecryptInit, PTA_CMD_AES128CTR_DecryptUpdate, PTA_CMD_AES128CTR_DecryptFinal, AES_DEC_MODE},
    {"aes256ctr_enc", PTA_CMD_AES256CTR_EncryptInit, PTA_CMD_AES256CTR_EncryptUpdate, PTA_CMD_AES256CTR_EncryptFinal, AES_ENC_MODE},
    {"aes256ctr_dec", PTA_CMD_AES256CTR_DecryptInit, PTA_CMD_AES256CTR_DecryptUpdate, PTA_CMD_AES256CTR_DecryptFinal, AES_DEC_MODE},
    {}
};

static uint32_t inp_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t out_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t iv0_buff[AES_BLOCK_SIZE  / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "AES Encryption\n");
    fprintf(stderr, "Usage: %s -a [-t <ALGO>] <KEY> <PLAIN> <CIPHER> \n", program);
    fprintf(stderr, "\t-t <ALGO>        AES Encryption Algorithm. \n");
    fprintf(stderr, "\t                 Use default \"aes128ecb_enc\" if not set.\n");
    fprintf(stderr, "\t                 - \"aes128ecb_enc\", \"aes256ecb_enc\" \n");
    fprintf(stderr, "\t                 - \"aes128cbc_enc\", \"aes256cbc_enc\" \n");
    fprintf(stderr, "\t                 - \"aes128ctr_enc\", \"aes256ctr_enc\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped AES key. \n");
    fprintf(stderr, "\t<PLAIN>          Specify the file name of the plain data to input. \n");
    fprintf(stderr, "\t<CIPHER>         Specify the file name of the cipher data to be output. \n");
    fprintf(stderr, "\n");
    fprintf(stderr, "AES Decryption\n");
    fprintf(stderr, "Usage: %s -a [-t <ALGO>] <KEY> <CIPHER> <PLAIN> \n", program);
    fprintf(stderr, "\t-t <ALGO>        AES Encryption Algorithm. \n");
    fprintf(stderr, "\t                 - \"aes128ecb_dec\", \"aes256ecb_dec\" \n");
    fprintf(stderr, "\t                 - \"aes128cbc_dec\", \"aes256cbc_dec\" \n");
    fprintf(stderr, "\t                 - \"aes128ctr_dec\", \"aes256ctr_dec\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped AES key. \n");
    fprintf(stderr, "\t<CIPHER>         Specify the file name of the cipher data to input. \n");
    fprintf(stderr, "\t<PLAIN>          Specify the file name of the plain data to be output. \n");
    fprintf(stderr, "\n");
    exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *aes_opt = "aes128ecb_enc";
    struct aes_info *info = NULL;

    while (-1 != (opt = getopt(argc, argv, "t:h"))) {      
        switch (opt) {
        case 't':
            aes_opt = optarg;
            break;
        case 'h' :
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    for (int i = 0; NULL != aes_list[i].aes_opt; i++) {
        if (!strcasecmp(aes_opt, aes_list[i].aes_opt)) {
            info = &aes_list[i];
            break;
        }
    }
    if (NULL == info) {
        fprintf(stderr, "Bad <ALGO> \"%s\" \n", aes_opt);
        usage(argv[0]);
    }
    
    if ((optind + 3) > argc) {
        fprintf(stderr, "Cannot find <KEY>, <PLAIN> or <CIPHER> \n");
        usage(argv[0]);
    }

    ctx->init     = info->init;
    ctx->update   = info->update;
    ctx->final    = info->final;
    ctx->mode     = info->mode;
    ctx->wuk_file = argv[optind];
    ctx->inp_file = argv[optind + 1];
    ctx->out_file = argv[optind + 2];
}

static int prepare_tee_session(struct sample_ctx *ctx)
{
    TEEC_UUID uuid = PTA_SCE_AES_UUID;
    uint32_t origin;
    TEEC_Result res;

    /* Initialize a context connecting us to the TEE */
    res = TEEC_InitializeContext(NULL, &ctx->ctx);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InitializeContext failed with code 0x%x\n", res);
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

static int set_init_vec(struct sample_ctx *ctx, uint32_t *iv, uint32_t *iv_sz)
{
    if ((PTA_CMD_AES128ECB_EncryptInit == ctx->init) ||
        (PTA_CMD_AES128ECB_DecryptInit == ctx->init) ||
        (PTA_CMD_AES256ECB_EncryptInit == ctx->init) ||
        (PTA_CMD_AES256ECB_DecryptInit == ctx->init) ){
        *iv_sz = 0;
        return 0;
    }
    if (HW_SCE_AES_CBC_IV_BYTE_SIZE > *iv_sz) {
        fprintf(stderr, "Failed to allocate resource.\n");
        return -1;
    }
    memset(iv, 0xa5, HW_SCE_AES_CBC_IV_BYTE_SIZE);
    *iv_sz = HW_SCE_AES_CBC_IV_BYTE_SIZE;
    return 0;
}

static int aes_init(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *iv,
    uint32_t iv_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    if (0 == iv_sz)
        op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, 
            TEEC_NONE, TEEC_NONE);
    else
        op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, 
            TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);
    
    op.params[0].tmpref.buffer = &ctx->aes;
    op.params[0].tmpref.size = sizeof(ctx->aes);
    op.params[1].tmpref.buffer = wuk;
    op.params[1].tmpref.size = wuk_sz;
    op.params[2].tmpref.buffer = iv;
    op.params[2].tmpref.size = iv_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->init, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(INIT) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int aes_update(struct sample_ctx *ctx, uint32_t *in, uint32_t in_sz, uint32_t *out, 
    uint32_t *out_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, 
        TEEC_MEMREF_TEMP_INOUT, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->aes;
    op.params[0].tmpref.size = sizeof(ctx->aes);
    op.params[1].tmpref.buffer = in;
    op.params[1].tmpref.size = in_sz;
    op.params[2].tmpref.buffer = out;
    op.params[2].tmpref.size = *out_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->update, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(UPDATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *out_sz = op.params[2].tmpref.size;
    return 0;
}

static int aes_final(struct sample_ctx *ctx)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->aes;
    op.params[0].tmpref.size = sizeof(ctx->aes);

    res = TEEC_InvokeCommand(&ctx->sess, ctx->final, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(FINAL) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int cipher_buffer(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *in,
    uint32_t in_sz, uint32_t *out, uint32_t *out_sz, uint32_t *iv, uint32_t iv_sz)
{
    int res;
    int err;

    res = aes_init(ctx, wuk, wuk_sz, iv, iv_sz);
    if (res) 
        return res;
    
    err = aes_update(ctx, in, in_sz, out, out_sz);
    if (err)
        res = err;

    err = aes_final(ctx);
    if (!res)
        res = err;

    return res;
}

int aes_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    uint32_t inp_size = sizeof(inp_buff);
    uint32_t out_size = sizeof(out_buff);
    uint32_t wuk_size = sizeof(wuk_buff);
    uint32_t iv0_size = sizeof(iv0_buff);

    memset(inp_buff, 0, sizeof(inp_buff));
    memset(out_buff, 0, sizeof(out_buff));
    memset(wuk_buff, 0, sizeof(wuk_buff));
    memset(iv0_buff, 0, sizeof(iv0_buff));

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if (res)
        goto err;

    printf("Load the wrapped aes key \"%s\"\n", ctx.wuk_file);
    res = load_file(ctx.wuk_file, wuk_buff, &wuk_size);
    if (res)
        goto err;

    printf("Load the input data from file \"%s\"\n", ctx.inp_file);
    res = load_file(ctx.inp_file, inp_buff, &inp_size);
    if (res)
        goto err;
    inp_size = (inp_size + (AES_BLOCK_SIZE - 1)) & (~(AES_BLOCK_SIZE - 1));
    
    printf("Set the initialization vector\n");
    res = set_init_vec(&ctx, iv0_buff, &iv0_size);
    if (res)
        goto err;

    printf("Encode/Decode buffer from TA\n");
    res = cipher_buffer(&ctx, wuk_buff, wuk_size, inp_buff, inp_size, out_buff, &out_size,
        iv0_buff, iv0_size);
    if (res)
        goto err;

    printf("Save the output data to file \"%s\"\n", ctx.out_file);
    res = save_file(ctx.out_file, out_buff, out_size);
    if (res)
        goto err;

err:
    terminate_tee_session(&ctx);
    return 0;
}
