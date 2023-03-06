#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

#define AES_KEY_SIZE 128
#define AES_BLOCK_SIZE 16

int main(int argc, char *argv[]){
    
    if(argc < 3){
        printf("Usage: %s input_file output_file\n", argv[0]);
        return -1;
    }

    FILE *infile = fopen(argv[1], "rb"); // Read block
    FILE *outfile = fopen(argv[2], "wb");  // Write block 

    // Generate a 128-bit AES key 

    unsigned char aes_key[AES_KEY_SIZE/8] = {0x12, 0x34, 0x56, 0x78,
                                         0x9a, 0xbc, 0xde, 0xf0,
                                         0x11, 0x22, 0x33, 0x44,
                                         0x55, 0x66, 0x77, 0x88};

    // Read the initialization vector (IV) from the input file
    unsigned char IV[AES_BLOCK_SIZE];
    fread(IV, 1, AES_BLOCK_SIZE, infile);

    // Initialize the AES cipher context
    AES_KEY aes_ctx;
    AES_set_decrypt_key(aes_key, AES_KEY_SIZE, &aes_ctx);

    // Buffers for encryption and decryption 
    unsigned char inbuf[AES_BLOCK_SIZE];
    unsigned char outbuf[AES_BLOCK_SIZE];

    memset(inbuf, 0, AES_BLOCK_SIZE); 

    int number_of_bytes_read = 0; 

    while((number_of_bytes_read = fread(inbuf, 1, AES_BLOCK_SIZE, infile)) > 0) {
        AES_cbc_encrypt(inbuf, outbuf, AES_BLOCK_SIZE, &aes_ctx, IV, AES_DECRYPT);
        fwrite(outbuf, 1, AES_BLOCK_SIZE, outfile);
        memset(inbuf, 0, AES_BLOCK_SIZE); 
    }

    // close the input and output files 
    fclose(infile);
    fclose(outfile);

    return 0; 
}
