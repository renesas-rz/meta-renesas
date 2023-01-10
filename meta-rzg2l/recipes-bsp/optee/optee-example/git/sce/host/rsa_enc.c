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
#include <pta_sce_rsa.h>

#define DAT_BUFFER_SIZE     (HW_SCE_RSA_4096_DATA_BYTE_SIZE)
#define KEY_BUFFER_SIZE     (1024)

#define RSA_ENC_MODE        (1)
#define RSA_DEC_MODE        (0)

struct rsa_info {
    char *rsa_opt;
    uint32_t cmd;
    uint32_t mode;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    uint32_t cmd;
    uint32_t mode;
    char *inp_file;
    char *out_file;
    char *wuk_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);
extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct rsa_info rsa_list[] = {
    {"rsaes_pkcs1024_enc", PTA_CMD_RSAES_PKCS1024_Encrypt, RSA_ENC_MODE},
    {"rsaes_pkcs1024_dec", PTA_CMD_RSAES_PKCS1024_Decrypt, RSA_DEC_MODE},
    {"rsaes_pkcs2048_enc", PTA_CMD_RSAES_PKCS2048_Encrypt, RSA_ENC_MODE},
    {"rsaes_pkcs2048_dec", PTA_CMD_RSAES_PKCS2048_Decrypt, RSA_DEC_MODE},
    {"rsaes_pkcs4096_enc", PTA_CMD_RSAES_PKCS4096_Encrypt, RSA_ENC_MODE},
    {}
};

static uint32_t inp_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t out_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "RSA Encryption\n");
    fprintf(stderr, "Usage: %s -s [-t <ALGO>] <KEY> <PLAIN> <CIPHER>\n", program);
    fprintf(stderr, "\t-t <ALGO>        RSA Encryption Algorithm.\n");
    fprintf(stderr, "\t                 Use default \"rsassa_pkcs1024_enc\" if not set.\n");
    fprintf(stderr, "\t                 - \"rsaes_pkcs1024_enc\" \n");
    fprintf(stderr, "\t                 - \"rsaes_pkcs2048_enc\" \n");
    fprintf(stderr, "\t                 - \"rsaes_pkcs4096_enc\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped RSA public key. \n");
    fprintf(stderr, "\t<PLAIN>          Specify the file name of the plain data to input. \n");
    fprintf(stderr, "\t<CIPHER>         Specify the file name of the cipher data to be output. \n");
    fprintf(stderr, "\n");
    fprintf(stderr, "RSA Decryption\n");
    fprintf(stderr, "Usage: %s -s [-t <ALGO>] <KEY> <CIPHER> <PLAIN> \n", program);
    fprintf(stderr, "\t-t <ALGO>        RSA Decryption Algorithm.\n");
    fprintf(stderr, "\t                 - \"rsaes_pkcs1024_dec\" \n");
    fprintf(stderr, "\t                 - \"rsaes_pkcs2048_dec\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped RSA private key. \n");
    fprintf(stderr, "\t<CIPHER>         Specify the file name of the cipher data to input. \n");
    fprintf(stderr, "\t<PLAIN>          Specify the file name of the plain data to be output. \n");
    fprintf(stderr, "\n");
	exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *rsa_opt = "rsaes_pkcs1024_enc";
    struct rsa_info *info = NULL;

    while (-1 != (opt = getopt(argc, argv, "t:h"))) {      
        switch (opt) {
        case 't':
            rsa_opt = optarg;
            break;
        case 'h':
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    for (int i = 0; NULL != rsa_list[i].rsa_opt; i++) {
        if (!strcasecmp(rsa_opt, rsa_list[i].rsa_opt)) {
            info = &rsa_list[i];
            break;
        }
    }
    if (NULL == info) {
        fprintf(stderr, "Bad <ALOG> \"%s\" \n", rsa_opt);
        usage(argv[0]);
    }

    if ((optind + 3) > argc) {
        fprintf(stderr, "Cannot find <KEY>, <PLAIN> or <CIPHER>. \n");
        usage(argv[0]);
    }

    ctx->cmd      = info->cmd;
    ctx->mode     = info->mode;
    ctx->wuk_file = argv[optind]; 
    ctx->inp_file = argv[optind + 1];
    ctx->out_file = argv[optind + 2];
}

static int prepare_tee_session(struct sample_ctx *ctx)
{
    TEEC_UUID uuid = PTA_SCE_RSA_UUID;
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

static int cipher_buffer(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *in, 
    uint32_t in_sz, uint32_t *out, uint32_t *out_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INOUT, 
        TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);

    op.params[0].tmpref.buffer = in;
    op.params[0].tmpref.size = in_sz;
    op.params[1].tmpref.buffer = out;
    op.params[1].tmpref.size = *out_sz;
    op.params[2].tmpref.buffer = wuk;
    op.params[2].tmpref.size = wuk_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->cmd, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(CIPHER) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *out_sz = op.params[1].tmpref.size;
    return 0;
}

int rsa_enc_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    uint32_t inp_size = sizeof(inp_buff);
    uint32_t out_size = sizeof(out_buff);
    uint32_t wuk_size = sizeof(wuk_buff);
    
    memset(inp_buff, 0, sizeof(inp_buff));
    memset(out_buff, 0, sizeof(out_buff));
    memset(wuk_buff, 0, sizeof(wuk_buff));

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if (res)
        goto err;
    
    printf("Load the wrapped rsa key \"%s\"\n", ctx.wuk_file);
    res = load_file(ctx.wuk_file, wuk_buff, &wuk_size);
    if (res)
        goto err;
        
    printf("Load the input data from file \"%s\"\n", ctx.inp_file);
    res = load_file(ctx.inp_file, inp_buff, &inp_size);
    if (res)
        goto err;

    printf("Encode/Decode buffer from TA\n");
    res = cipher_buffer(&ctx, wuk_buff, wuk_size, inp_buff, inp_size, out_buff, &out_size);
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
