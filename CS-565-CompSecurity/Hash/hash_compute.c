#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);

    // Hash functions to use
    const EVP_MD *md_sha256 = EVP_sha256();
    const EVP_MD *md_sha512 = EVP_sha512();
    const EVP_MD *md_sha3_256 = EVP_sha3_256();

    // Buffers for reading files
    char buf[BUFSIZE];
    size_t n;

    // Compute hash of file1 with SHA-256
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        perror("EVP_MD_CTX_new");
        return 1;
    }
    if (!EVP_DigestInit_ex(mdctx, md_sha256, NULL)) {
        perror("EVP_DigestInit_ex");
        return 1;
    }
    FILE *fp = fopen(file1, "rb");
    if (!fp) {
        perror(file1);
        return 1;
    }
    while ((n = fread(buf, 1, BUFSIZE, fp)) > 0) {
        if (!EVP_DigestUpdate(mdctx, buf, n)) {
            perror("EVP_DigestUpdate");
            return 1;
        }
    }
    fclose(fp);
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashlen;
    if (!EVP_DigestFinal_ex(mdctx, hash, &hashlen)) {
        perror("EVP_DigestFinal_ex");
        return 1;
    }
    EVP_MD_CTX_free(mdctx);

    printf("%s SHA-256 hash: ", file1);
    for (unsigned int i = 0; i < hashlen; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Compute hash of file1 with SHA-512
    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        perror("EVP_MD_CTX_new");
        return 1;
    }
    if (!EVP_DigestInit_ex(mdctx, md_sha512, NULL)) {
        perror("EVP_DigestInit_ex");
        return 1;
    }
    fp = fopen(file1, "rb");
    if (!fp) {
        perror(file1);
        return 1;
    }
    while ((n = fread(buf, 1, BUFSIZE, fp)) > 0) {
        if (!EVP_DigestUpdate(mdctx, buf, n)) {
            perror("EVP_DigestUpdate");
            return 1;
        }
    }
    fclose(fp);
    if (!EVP_DigestFinal_ex(mdctx, hash, &hashlen)) {
        perror("EVP_DigestFinal_ex");
        return 1;
    }
    EVP_MD_CTX_free(mdctx);

    printf("%s SHA-512 hash: ", file1);
    for (unsigned int i = 0; i < hashlen; i++) {
        printf("%02x", hash[i]);
    }
    printf

