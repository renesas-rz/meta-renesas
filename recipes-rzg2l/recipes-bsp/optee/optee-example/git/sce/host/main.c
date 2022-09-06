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
#include <sys/stat.h>

extern int upd_key_main(int argc, char *argv[]);
extern int gen_key_main(int argc, char *argv[]);
extern int random_main(int argc, char *argv[]);
extern int aes_main(int argc, char *argv[]);
extern int mac_main(int argc, char *argv[]);
extern int sha_main(int argc, char *argv[]);
extern int rsa_sig_main(int argc, char *argv[]);
extern int rsa_enc_main(int argc, char *argv[]);
extern int ecc_sig_main(int argc, char *argv[]);

static void usage(char *program)
{
    fprintf(stderr, "Usage: %s [Options]\n", program);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "\t-k               Wrapped User Key Generation\n");
    fprintf(stderr, "\t-u               User Key Update\n");
    fprintf(stderr, "\t-g               Random Number Generation\n");
    fprintf(stderr, "\t-a               AES Encryption/Decryption\n");
    fprintf(stderr, "\t-m               MAC Generation/Verification\n");
    fprintf(stderr, "\t-d               HASH Generation \n");
    fprintf(stderr, "\t-r               RSA Signature Generation/Verification\n");
    fprintf(stderr, "\t-s               RSA Encryption/Decryption\n");
    fprintf(stderr, "\t-e               ECDSA Signature Generation/Verification\n");
    fprintf(stderr, "\t-h               Print this help\n");
    fprintf(stderr, "\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    int opt = 0;

    if (2 > argc) {
        usage(argv[0]);
        return -1;
    }

    opt = getopt(2, argv, "kugamdrseh");
    switch (opt) {
    case 'k':
        return gen_key_main(argc, argv);
    case 'u':
        return upd_key_main(argc, argv);
    case 'g':
        return random_main(argc, argv);
    case 'a':
        return aes_main(argc, argv);
    case 'm':
        return mac_main(argc, argv);
    case 'd':
        return sha_main(argc, argv);
    case 'r':
        return rsa_sig_main(argc, argv);
    case 's':
        return rsa_enc_main(argc, argv);
    case 'e':
        return ecc_sig_main(argc, argv);
    case 'h':
        usage(argv[0]);
        return -1;
    default:
        usage(argv[0]);
        return -1;
    }
    return 0;
}

int load_file(char *file_name, uint32_t *buf, uint32_t *buf_sz)
{
    int res = 0;
    FILE *fp;
    struct stat statBuf;

    if ((!file_name) || (!buf) || (!buf_sz)) {
        fprintf(stderr, "load_file: Bad arguments\n");
        return -1;
    }

    if (0 != stat(file_name, &statBuf)) {
        fprintf(stderr, "Failed to get size: \"%s\"\n", strerror(errno));
        return -1;
    }
    if (*buf_sz < statBuf.st_size) {
        fprintf(stderr, "Bad file size: \"%d\"\n", *buf_sz);
        return -1;
    }
    if ((fp = fopen(file_name, "rb")) == NULL) {
        fprintf(stderr, "Failed to open: \"%s\"\n", file_name);
        return -1;
    }
    *buf_sz = statBuf.st_size;
    if (*buf_sz > fread(buf, 1, *buf_sz, fp)) {
        fprintf(stderr, "Failed to read: \"%s\"\n", strerror(errno));
        res = -1;
    }
    fclose(fp);
    return res;
}

int save_file(char *file_name, uint32_t *buf, uint32_t buf_sz)
{
    int res = 0;
    FILE *fp;

    if ((!file_name) || (!buf)) {
        fprintf(stderr, "save_file: Bad arguments\n");
        return -1;
    }

    if ((fp = fopen(file_name, "wb")) == NULL) {
        fprintf(stderr, "Failed to open: \"%s\"\n", file_name);
        return -1;
    }
    if (buf_sz > fwrite(buf, 1, buf_sz, fp)) {
        fprintf(stderr, "Failed to write: \"%s\"\n", strerror(errno));
        res = -1;
    }
    fclose(fp);
    return res;
}
