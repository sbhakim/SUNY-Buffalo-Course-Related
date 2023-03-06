

/* The following program takes 2 input from the user. First argument is the name of the file to encrypt 
and the second argument is the name of the after enryption operation is completed. */

#include <stdio.h>
#include <string.h>
#include <openssl/aes.h> 
#include <time.h>
#include <sys/time.h>


#define AES_KEY_SIZE 128
#define AES_BLOCK_SIZE 16

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
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

    unsigned char aes_key[AES_KEY_SIZE/8] = {0x12, 0x34, 0x56, 0x78,
                                         0x9a, 0xbc, 0xde, 0xf0,
                                         0x11, 0x22, 0x33, 0x44,
                                         0x55, 0x66, 0x77, 0x88};


    // Generate a random 128-bit initialization vector (IV)
    unsigned char IV[AES_BLOCK_SIZE];
    memset (IV, 0xff, AES_BLOCK_SIZE);
   // RAND_bytes(IV, AES_BLOCK_SIZE); 

    if (RAND_bytes(IV, AES_BLOCK_SIZE) != 1) {
        fprintf(stderr, "Error: Failed to generate random IV.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }


    // Write the initialization vector (IV) to the output file

    // fwrite(IV, 1, AES_BLOCK_SIZE, outfile); 

    // Write the initialization vector (IV) to the output file
    if (fwrite(IV, 1, AES_BLOCK_SIZE, outfile) != AES_BLOCK_SIZE) {
        fprintf(stderr, "Error: Failed to write IV to output file.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    // Initialize the AES ciphter context

    AES_KEY aes_ctx;
    // AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &aes_ctx); 

     if (AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &aes_ctx) != 0) {
        fprintf(stderr, "Error: Failed to set up AES cipher context.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    // Buffers for encryption and decryption 
    unsigned char inbuf[AES_BLOCK_SIZE];    // input buffer
    unsigned char outbuf[AES_BLOCK_SIZE];

    memset(inbuf, 0, AES_BLOCK_SIZE);      // initializing the input buffer with 0 

    int number_of_bytes_read = 0; 

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);      // calculate the time to encrypt the file

    while((number_of_bytes_read = fread(inbuf, 1, AES_BLOCK_SIZE, infile)) > 0) {
        AES_cbc_encrypt(inbuf, outbuf, AES_BLOCK_SIZE, &aes_ctx, IV, AES_ENCRYPT);
        // fwrite(outbuf, 1, AES_BLOCK_SIZE, outfile);
        if (fwrite(outbuf, 1, AES_BLOCK_SIZE, outfile) != AES_BLOCK_SIZE) {
            fprintf(stderr, "Error: Failed to write encrypted data to output file.\n");
            fclose(infile);
            fclose(outfile);
            return 1;
        }
        memset(inbuf, 0, AES_BLOCK_SIZE); 
    }
    gettimeofday(&end_time, NULL); 
    // convert microseconds to seconds divide by 1000000
    double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0; 

    long int file_size;
    fseek(infile, 0L, SEEK_END);
    file_size = ftell(infile);
    rewind(infile);

    double speed_change = file_size / time_taken;

    printf("Time taken to encrypt the file: %f seconds\n", time_taken);
    printf("Encryption speed: %f MB/s\n", speed_change/1000000.0);



    // close the input and output files 
    fclose(infile);
    fclose(outfile);

    return 0; 
}
