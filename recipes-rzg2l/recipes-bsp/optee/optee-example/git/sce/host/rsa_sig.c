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

#define SIG_BUFFER_SIZE     (1024)
#define KEY_BUFFER_SIZE     (1024)
#define DAT_BUFFER_SIZE     (512)

#define RSA_GEN_MODE        (1)
#define RSA_VER_MODE        (0)

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
    char *msg_file;
    char *sig_file;
    char *wuk_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);
extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct rsa_info rsa_list[] = {
    {"rsassa_pkcs1024_gen", PTA_CMD_RSASSA_PKCS1024_SignatureGenerate, RSA_GEN_MODE},
    {"rsassa_pkcs1024_ver", PTA_CMD_RSASSA_PKCS1024_SignatureVerify,   RSA_VER_MODE},
    {"rsassa_pkcs2048_gen", PTA_CMD_RSASSA_PKCS2048_SignatureGenerate, RSA_GEN_MODE},
    {"rsassa_pkcs2048_ver", PTA_CMD_RSASSA_PKCS2048_SignatureVerify,   RSA_VER_MODE},
    {"rsassa_pkcs4096_ver", PTA_CMD_RSASSA_PKCS4096_SignatureVerify,   RSA_VER_MODE},
    {}
};

static uint32_t msg_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t sig_buff[SIG_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "RSA Signature Generation\n");
    fprintf(stderr, "Usage: %s -r [-t <ALGO>] <KEY> <MESSAGE> <SIGNATURE> \n", program);
    fprintf(stderr, "\t-t <ALGO>        Signature Generation Algorithm. \n");
    fprintf(stderr, "\t                 Use default \"rsassa_pkcs1024_gen\" if not set.\n");
    fprintf(stderr, "\t                 - \"rsassa_pkcs1024_gen\" \n");
    fprintf(stderr, "\t                 - \"rsassa_pkcs2048_gen\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped RSA private key. \n");
    fprintf(stderr, "\t<MESSAGE>        Specify the file name of the message to input. \n");
    fprintf(stderr, "\t<SIGNATURE>      Specify the file name of the signature to be output. \n");
    fprintf(stderr, "\n");
    fprintf(stderr, "RSA Signature Verification\n");
    fprintf(stderr, "Usage: %s -r [-t <ALGO>] <KEY> <MESSAGE> <SIGNATURE> \n", program);
    fprintf(stderr, "\t-t <ALGO>        Signature Verification Algorithm. \n");
    fprintf(stderr, "\t                 - \"rsassa_pkcs1024_ver\" \n");
    fprintf(stderr, "\t                 - \"rsassa_pkcs2048_ver\" \n");
    fprintf(stderr, "\t                 - \"rsassa_pkcs4096_ver\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped RSA public key. \n");
    fprintf(stderr, "\t<MESSAGE>        Specify the file name of the message to input. \n");
    fprintf(stderr, "\t<SIGNATURE>      Specify the file name of the signature to input. \n");
    fprintf(stderr, "\n");
	exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *rsa_opt = "rsassa_pkcs1024_gen";
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
        fprintf(stderr, "Bad <ALGO> \"%s\" \n", rsa_opt);
        usage(argv[0]);
    }

    if ((optind + 3) > argc) {
        fprintf(stderr, "Cannot find <KEY>, <MESSAGE> or <SIGNATURE>. \n");
        usage(argv[0]);
    }

    ctx->cmd      = info->cmd;
    ctx->mode     = info->mode;
    ctx->wuk_file = argv[optind];
    ctx->msg_file = argv[optind + 1];
    ctx->sig_file = argv[optind + 2];
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

static int generate_signature(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *msg, 
    uint32_t msg_sz, uint32_t *sig, uint32_t *sig_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INOUT, 
        TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);

    op.params[0].tmpref.buffer = msg;
    op.params[0].tmpref.size = msg_sz;
    op.params[1].tmpref.buffer = sig;
    op.params[1].tmpref.size = *sig_sz;
    op.params[2].tmpref.buffer = wuk;
    op.params[2].tmpref.size = wuk_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->cmd, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(GENERATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *sig_sz = op.params[1].tmpref.size;
    return 0;
}

static int verify_signature(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *msg, 
    uint32_t msg_sz, uint32_t *sig, uint32_t sig_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT, 
        TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);

    op.params[0].tmpref.buffer = sig;
    op.params[0].tmpref.size = sig_sz;
    op.params[1].tmpref.buffer = msg;
    op.params[1].tmpref.size = msg_sz;
    op.params[2].tmpref.buffer = wuk;
    op.params[2].tmpref.size = wuk_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->cmd, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(VERIFY) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

int rsa_sig_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    uint32_t msg_size = sizeof(msg_buff);
    uint32_t sig_size = sizeof(sig_buff);
    uint32_t wuk_size = sizeof(wuk_buff);

    memset(msg_buff, 0, sizeof(msg_buff));
    memset(sig_buff, 0, sizeof(sig_buff));
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

    printf("Load the message from file \"%s\"\n", ctx.msg_file);
    res = load_file(ctx.msg_file, msg_buff, &msg_size);
    if (res)
        goto err;

    if (RSA_GEN_MODE == ctx.mode) {
        printf("Generate the signature with TA\n");
        res = generate_signature(&ctx, wuk_buff, wuk_size, msg_buff, msg_size, sig_buff, &sig_size);
        if (res)
            goto err;
        
        printf("Save the generated signature to file \"%s\"\n", ctx.sig_file);
        res = save_file(ctx.sig_file, sig_buff, sig_size);
        if (res)
            goto err;
    }
    else {
        printf("Load the signature from file \"%s\"\n", ctx.sig_file);
        res = load_file(ctx.sig_file, sig_buff, &sig_size);
        if (res)
            goto err;
        
        printf("Verify the signature with TA\n");
        res = verify_signature(&ctx, wuk_buff, wuk_size, msg_buff, msg_size, sig_buff, sig_size);
        if (res)
            goto err;
        
        printf("\nSignature Verification Passed.\n\n");
    }

err:
    terminate_tee_session(&ctx);
    return 0;
}
