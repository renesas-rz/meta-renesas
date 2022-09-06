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
#include <pta_sce_sha.h>

#define MSG_DIGEST_SIZE     (64)
#define DAT_BUFFER_SIZE     (256)

struct sha_info {
    char *sha_opt;
    uint32_t init;
    uint32_t update;
    uint32_t final;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    sce_sha_md5_handle_t sha;
    uint32_t init;
    uint32_t update;
    uint32_t final;
    char *msg_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);

static struct sha_info sha_list[] = {
    {"sha224", PTA_CMD_SHA224_Init, PTA_CMD_SHA224_Update, PTA_CMD_SHA224_Final},
    {"sha256", PTA_CMD_SHA256_Init, PTA_CMD_SHA256_Update, PTA_CMD_SHA256_Final},
    {}
};

static uint32_t msg_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t out_buff[MSG_DIGEST_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "Hash Value Generation\n");
    fprintf(stderr, "Usage: %s -d [-t <ALGO>] <MESSAGE> \n", program);
    fprintf(stderr, "\t-t <ALGO>        Secure Hash Algorithm. \n");
    fprintf(stderr, "\t                 Use default \"sha224\" if not set.\n");
    fprintf(stderr, "\t                 - \"sha224\" \n");
    fprintf(stderr, "\t                 - \"sha256\" \n");
    fprintf(stderr, "\t<MESSAGE>        Specify the file name of the message to input. \n");
    fprintf(stderr, "\n");
	exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *sha_opt = "sha224";
    struct sha_info *info = NULL;
    

    while (-1 != (opt = getopt(argc, argv, "t:h"))) {      
        switch (opt) {
        case 't':
            sha_opt = optarg;
            break;
        case 'h' :
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    for (int i = 0; NULL != sha_list[i].sha_opt; i++) {
        if (!strcasecmp(sha_opt, sha_list[i].sha_opt)) {
            info = &sha_list[i];
            break;
        }
    }
    if (NULL == info) {
        fprintf(stderr, "Bad <ALGO> \"%s\" \n", sha_opt);
        usage(argv[0]);
    }
    
    if ((optind + 1) > argc) {
        fprintf(stderr, "Cannot find <FILE> \n");
        usage(argv[0]);
    }

    ctx->init     = info->init;
    ctx->update   = info->update;
    ctx->final    = info->final;
    ctx->msg_file = argv[optind];
}

static int prepare_tee_session(struct sample_ctx *ctx)
{
    TEEC_UUID uuid = PTA_SCE_SHA_UUID;
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

static int sha_init(struct sample_ctx *ctx)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->sha;
    op.params[0].tmpref.size = sizeof(ctx->sha);

    res = TEEC_InvokeCommand(&ctx->sess, ctx->init, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(INIT) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int sha_update(struct sample_ctx *ctx, uint32_t *in, uint32_t in_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->sha;
    op.params[0].tmpref.size = sizeof(ctx->sha);
    op.params[1].tmpref.buffer = in;
    op.params[1].tmpref.size = in_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->update, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(UPDATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int sha_final(struct sample_ctx *ctx, uint32_t *out, uint32_t *out_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->sha;
    op.params[0].tmpref.size = sizeof(ctx->sha);
    op.params[1].tmpref.buffer = out;
    op.params[1].tmpref.size = *out_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->final, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(FINAL) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *out_sz = op.params[1].tmpref.size; 
    return 0;
}

static int generate_hash(struct sample_ctx *ctx, uint32_t *in, uint32_t in_sz, uint32_t *out, uint32_t *out_sz)
{
    int res;
    int err;

    res = sha_init(ctx);
    if (res) 
        return res;
    
    err = sha_update(ctx, in, in_sz);
    if (err)
        res = err;

    err = sha_final(ctx, out, out_sz);
    if (!res)
        res = err;

    return res;
}

int sha_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    uint32_t msg_size = sizeof(msg_buff);
    uint32_t out_size = sizeof(out_buff);

    memset(msg_buff, 0, sizeof(msg_buff));
    memset(out_buff, 0, sizeof(out_buff));
    
    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if (res)
        goto err;

    printf("Load the message from file \"%s\"\n", ctx.msg_file);
    res = load_file(ctx.msg_file, msg_buff, &msg_size);
    if (res)
        goto err;

    printf("Generate hash with TA\n");
    res = generate_hash(&ctx, msg_buff, msg_size, out_buff, &out_size);
    if (res)
        goto err;

    printf("\nHash Data : 0x");
    for (int i = 0; i < out_size; i++) {
        printf("%02X", *((uint8_t *)out_buff + i));
    }
    printf("\n\n");

err:
    terminate_tee_session(&ctx);
    return 0;
}
