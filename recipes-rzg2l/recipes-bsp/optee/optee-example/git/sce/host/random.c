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

#define NUM_OF_RND_GEN      (16)
#define RND_BUFFER_SIZE     (NUM_OF_RND_GEN * 4)

/* TEE resources */
struct sample_ctx {
    TEEC_Context ctx;
    TEEC_Session sess;
    uint32_t num;
};

static uint32_t rnd_buff[RND_BUFFER_SIZE / sizeof(uint32_t)];

static void usage(char *program)
{
    fprintf(stderr, "Random Number Generation\n");
    fprintf(stderr, "Usage: %s -g [NUMBERS]\n", program);
    fprintf(stderr, "\n");
    fprintf(stderr, "\t[NUMBERS]        Specify in the range of 1 to %ld.\n", sizeof(rnd_buff));
    fprintf(stderr, "\t                 Use default 16 if not set.\n");
    fprintf(stderr, "\n");
	exit(1);
}

static void get_args(int argc, char *argv[], struct sample_ctx *ctx)
{
    int opt;
	char *ep;

    ctx->num = 16;

    while (-1 != (opt = getopt(argc, argv, "h"))) {      
        switch (opt) {
        case 'h':
            usage(argv[0]);
            break;
        default:
            usage(argv[0]);
            break;
        }
    }

    if ((optind + 1) <= argc) {
        ctx->num = strtol(argv[optind], &ep, 0);
        if (*ep) {
            fprintf(stderr, "Cannot parse [NUMBERS]: \"%s\"", argv[optind]);
            usage(argv[0]);
        }
    }
    if ((1 > ctx->num) || (sizeof(rnd_buff) < ctx->num)) {
        fprintf(stderr, "Bad [NUMBERS]: \"%d\" \n", ctx->num);
        usage(argv[0]);
    }
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

static int generate_random_number(struct sample_ctx *ctx, uint32_t *buff)
{
    TEEC_Operation op;
    uint32_t origin;
    TEEC_Result res;

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    op.params[0].tmpref.buffer = buff;
    op.params[0].tmpref.size = NUM_OF_RND_GEN;

    res = TEEC_InvokeCommand(&ctx->sess, PTA_CMD_RandomNumberGenerate, &op, &origin);
    if (res != TEEC_SUCCESS){
        fprintf(stderr, "TEEC_InvokeCommand(GENERATE) failed 0x%x origin 0x%x\n", res, origin);
        return -1;
    }
    return 0;
}

int random_main(int argc, char *argv[])
{
    int res;
    struct sample_ctx ctx;

    printf("Parse command line options\n");
    get_args(argc, argv, &ctx);

    printf("Prepare session with the TA\n");
    res = prepare_tee_session(&ctx);
    if(res)
        goto err;
    
    printf("Generate random number with the TA\n");
    for (int i = 0; i < ctx.num; i += NUM_OF_RND_GEN) {
        res = generate_random_number(&ctx, &rnd_buff[i / sizeof(uint32_t)]);
        if(res)
            goto err;
    }

    printf("\nGenerated Random Number :\n");
    for (int i = 0; i < ctx.num; i++) {
        printf("0x%02X, ", *((uint8_t *)rnd_buff + i));
    }
    printf("\n");

err:
    terminate_tee_session(&ctx);
    return 0;
}
