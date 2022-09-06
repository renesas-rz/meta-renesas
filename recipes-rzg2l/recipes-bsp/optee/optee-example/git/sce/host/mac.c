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

#define AES_BLOCK_SIZE      (16)
#define KEY_BUFFER_SIZE     (512)
#define DAT_BUFFER_SIZE     (1024)

#define MAC_GEN_MODE        (1)
#define MAC_VER_MODE        (0)

struct mac_info {
    char *mac_opt;
    uint32_t init;
    uint32_t update;
    uint32_t final;
    uint32_t mode;
};

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    sce_cmac_handle_t mac;
    uint32_t init;
    uint32_t update;
    uint32_t final;
    uint32_t mode;
    char *msg_file;
    char *mac_file;
    char *wuk_file;
};

extern int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz);
extern int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz);

static struct mac_info mac_list[] = {
    {"aes128mac_gen", PTA_CMD_AES128CMAC_GenerateInit, PTA_CMD_AES128CMAC_GenerateUpdate, PTA_CMD_AES128CMAC_GenerateFinal, MAC_GEN_MODE},
    {"aes128mac_ver", PTA_CMD_AES128CMAC_VerifyInit,   PTA_CMD_AES128CMAC_VerifyUpdate,   PTA_CMD_AES128CMAC_VerifyFinal,   MAC_VER_MODE},
    {"aes256mac_gen", PTA_CMD_AES256CMAC_GenerateInit, PTA_CMD_AES256CMAC_GenerateUpdate, PTA_CMD_AES256CMAC_GenerateFinal, MAC_GEN_MODE},
    {"aes256mac_ver", PTA_CMD_AES256CMAC_VerifyInit,   PTA_CMD_AES256CMAC_VerifyUpdate,   PTA_CMD_AES256CMAC_VerifyFinal,   MAC_VER_MODE},
    {}
};

static uint32_t msg_buff[DAT_BUFFER_SIZE / sizeof(uint32_t)];
static uint32_t mac_buff[AES_BLOCK_SIZE  / sizeof(uint32_t)];
static uint32_t wuk_buff[KEY_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "MAC Generation\n");
    fprintf(stderr, "Usage: %s -m [-t <ALGO>] <KEY> <MESSAGE> <MAC> \n", program);
    fprintf(stderr, "\t-t <ALGO>        MAC Generation Algorithm. \n");
    fprintf(stderr, "\t                 Use default \"aes128mac_gen\" if not set.\n");
    fprintf(stderr, "\t                 - \"aes128mac_gen\", \"aes256mac_gen\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped AES key. \n");
    fprintf(stderr, "\t<MESSAGE>        Specify the file name of the message to input. \n");
    fprintf(stderr, "\t<MAC>            Specify the file name of the mac to be output. \n");
    fprintf(stderr, "\n");
    fprintf(stderr, "MAC Verification\n");
    fprintf(stderr, "Usage: %s -m [-t <ALGO>] <KEY> <CIPHER> <PLAIN> \n", program);
    fprintf(stderr, "\t-t <ALGO>        MAC Verification Algorithm. \n");
    fprintf(stderr, "\t                 - \"aes128mac_ver\", \"aes256mac_ver\" \n");
    fprintf(stderr, "\t<KEY>            Specify the file name of the wrapped AES key. \n");
    fprintf(stderr, "\t<MESSAGE>        Specify the file name of the message to input. \n");
    fprintf(stderr, "\t<MAC>            Specify the file name of the mac to be input. \n");
    fprintf(stderr, "\n");
    exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
    char *mac_opt = "aes128mac_gen";
    struct mac_info *info = NULL;

    while (-1 != (opt = getopt(argc, argv, "t:h"))) {      
        switch (opt) {
        case 't':
            mac_opt = optarg;
            break;
        case 'h' :
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    for (int i = 0; NULL != mac_list[i].mac_opt; i++) {
        if (!strcasecmp(mac_opt, mac_list[i].mac_opt)) {
            info = &mac_list[i];
            break;
        }
    }
    if (NULL == info) {
        fprintf(stderr, "Bad <ALGO> \"%s\" \n", mac_opt);
        usage(argv[0]);
    }
    
    if ((optind + 3) > argc) {
        fprintf(stderr, "Cannot find <KEY>, <MESSAGE> or <MAC> \n");
        usage(argv[0]);
    }

    ctx->init     = info->init;
    ctx->update   = info->update;
    ctx->final    = info->final;
    ctx->mode     = info->mode;
    ctx->wuk_file = argv[optind];
    ctx->msg_file = argv[optind + 1];
    ctx->mac_file = argv[optind + 2];
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

static int mac_init(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE);
    
    op.params[0].tmpref.buffer = &ctx->mac;
    op.params[0].tmpref.size = sizeof(ctx->mac);
    op.params[1].tmpref.buffer = wuk;
    op.params[1].tmpref.size = wuk_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->init, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(INIT) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int mac_update(struct sample_ctx *ctx, uint32_t *msg, uint32_t msg_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->mac;
    op.params[0].tmpref.size = sizeof(ctx->mac);
    op.params[1].tmpref.buffer = msg;
    op.params[1].tmpref.size = msg_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->update, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(UPDATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

static int mac_final(struct sample_ctx *ctx, uint32_t *mac, uint32_t *mac_sz)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    if (MAC_GEN_MODE == ctx->mode)
        op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE);
    else
        op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = &ctx->mac;
    op.params[0].tmpref.size = sizeof(ctx->mac);
    op.params[1].tmpref.buffer = mac;
    op.params[1].tmpref.size = *mac_sz;

    res = TEEC_InvokeCommand(&ctx->sess, ctx->final, &op, &origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand(FINAL) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    *mac_sz = op.params[1].tmpref.size;
    return 0;
}

static int msg_auth_code(struct sample_ctx *ctx, uint32_t *wuk, uint32_t wuk_sz, uint32_t *msg,
    uint32_t msg_sz, uint32_t *mac, uint32_t *mac_sz)
{
    int res;
    int err;

    if (ctx->init) {
        res = mac_init(ctx, wuk, wuk_sz);
        if (res) 
            return res;
    }
    else {

    }
    
    err = mac_update(ctx, msg, msg_sz);
    if (err)
        res = err;

    err = mac_final(ctx, mac, mac_sz);
    if (!res)
        res = err;

    return res;
}

int mac_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    uint32_t msg_size = sizeof(msg_buff);
    uint32_t mac_size = sizeof(mac_buff);
    uint32_t wuk_size = sizeof(wuk_buff);

    memset(msg_buff, 0, sizeof(msg_buff));
    memset(mac_buff, 0, sizeof(mac_buff));
    memset(wuk_buff, 0, sizeof(wuk_buff));

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if (res)
        goto err;

    printf("Load the wrapped aes key from file \"%s\"\n", ctx.wuk_file);
    res = load_file(ctx.wuk_file, wuk_buff, &wuk_size);
    if (res)
        goto err;

    printf("Load the message from file \"%s\"\n", ctx.msg_file);
    res = load_file(ctx.msg_file, msg_buff, &msg_size);
    if (res)
        goto err;

    if (MAC_GEN_MODE == ctx.mode) {
        printf("MAC Generation with TA\n");
        res = msg_auth_code(&ctx, wuk_buff, wuk_size, msg_buff, msg_size, mac_buff, &mac_size);
        if (res)
            goto err;

        printf("Save the mac to file \"%s\"\n", ctx.mac_file);
        res = save_file(ctx.mac_file, mac_buff, mac_size);
        if (res)
            goto err;
    }
    else {
        printf("Load the mac from file \"%s\"\n", ctx.mac_file);
        res = load_file(ctx.mac_file, mac_buff, &mac_size);
        if (res)
            goto err;

        printf("MAC Verification with TA\n");
        res = msg_auth_code(&ctx, wuk_buff, wuk_size, msg_buff, msg_size, mac_buff, &mac_size);
        if (res)
            goto err;
        
        printf("\nMAC Verification Passed.\n\n");
    }

err:
    terminate_tee_session(&ctx);
    return 0;
}
