#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_KEY_SIZE 128
#define AES_BLOCK_SIZE 16

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb"); // Read block
    if (infile == NULL) {
        fprintf(stderr, "Error: could not open input file '%s'\n", argv[1]);
        return 1;
    }

    FILE *outfile = fopen(argv[2], "wb");  // Write block 
    if (outfile == NULL) {
        fprintf(stderr, "Error: could not open output file '%s'\n", argv[2]);
        fclose(infile);
        return 1;
    }

    // Generate a 128-bit AES key 
    const char *key_str = "university at buffalo";
    unsigned char aes_key[AES_KEY_SIZE/8];
    memcpy(aes_key, key_str, strlen(key_str));

    // Generate a random 128-bit initialization vector (IV)
    unsigned char IV[AES_BLOCK_SIZE];
    memset (IV, 0xff, AES_BLOCK_SIZE);
    RAND_bytes(IV, AES_BLOCK_SIZE);

    // Write the initialization vector (IV) to the output file
    fwrite(IV, 1, AES_BLOCK_SIZE, outfile);

    // Initialize the AES cipher context
    AES_KEY aes_ctx;
    AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &aes_ctx);

    // Buffers for encryption and decryption 
    unsigned char inbuf[AES_BLOCK_SIZE];    // input buffer
    unsigned char outbuf[AES_BLOCK_SIZE];   // output buffer
    unsigned char ctr[AES_BLOCK_SIZE];      // counter buffer

    memset(ctr, 0, AES_BLOCK_SIZE);
    ctr[AES_BLOCK_SIZE-1] = 0x01;           // initialize counter to 1

    int number_of_bytes_read = 0; 

    while((number_of_bytes_read = fread(inbuf, 1, AES_BLOCK_SIZE, infile)) > 0) {
        AES_ctr128_encrypt(inbuf, outbuf, number_of_bytes_read, &aes_ctx, IV, ctr, &AES_ctr128_encrypt);
        fwrite(outbuf, 1, number_of_bytes_read, outfile);
        memset(inbuf, 0, AES_BLOCK_SIZE); 
    }

    // close the input and output files 
    fclose(infile);
    fclose(outfile);

    return 0; 
}
