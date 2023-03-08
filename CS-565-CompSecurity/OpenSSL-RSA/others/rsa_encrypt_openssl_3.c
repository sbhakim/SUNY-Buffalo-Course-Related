#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>


#define BUFSIZE 1024 


int main(int argc, char * argv[]){
	if (argc < 5)
	{
		printf("Usage: %s <public_key_file> <private_key_file> <input_file> <output_file>\n", argv[0]);
		exit(1);
	}


	char *public_key_file = argv[1];
	char *private_key_file = argv[2];
	char *input_file = argv[3];
	char *output_file = argv[4];

	EVP_PKEY *public_key = NULL, *private_key = NULL;

	// Read public key from file 
	FILE *pub_fp = fopen(public_key_file, "rb"); 
	if (!pub_fp) {
		printf("Error opening public key file \n");
		exit(1);
	}

	
	fseek(pub_fp, 0, SEEK_END);
    long pub_size = ftell(pub_fp);
    fseek(pub_fp, 0, SEEK_SET);

    size_t *pub_buf = (size_t *) malloc(pub_size);
    if (!pub_buf) {
   		 printf("Error allocating memory for public key buffer\n");
    	exit(1);
	}

    
    fread(pub_buf, 1, pub_size, pub_fp);

    
    public_key = PEM_read_PUBKEY(BIO_new_mem_buf(pub_buf, pub_size), NULL, NULL, NULL);
	if (!public_key) {
    	printf("Error reading public key file \n");
    	exit(1);
	}
	fclose(pub_fp);

    free(pub_buf);

	// Read private key from file 

	FILE *priv_fp = fopen(private_key_file, "rb");
	if (!priv_fp) {
		printf ("Error opening private key file\n");
		exit(1);
	}

	fseek(priv_fp, 0, SEEK_END);
    long priv_size = ftell(priv_fp);
    fseek(priv_fp, 0, SEEK_SET);

    size_t *priv_buf = (size_t *) malloc(priv_size);
    if (!priv_buf) {
    	printf("Error allocating memory for private key buffer\n");
    	exit(1);
	}	
    fread(priv_buf, 1, priv_size, priv_fp);
    
    private_key = PEM_read_PrivateKey(BIO_new_mem_buf(priv_buf, priv_size), NULL, NULL, NULL);
	if (!private_key) {
    	printf("Error reading private key file \n");
    	exit(1);
	}
	fclose(priv_fp); 
    free(priv_buf);

    
	// Read input file 
	FILE *in_fp = fopen(input_file, "rb");
	if(!in_fp){
		printf ("Error opening input file\n");
		exit(1);
	}

	// Create output file
	FILE *out_fp  = fopen(output_file, "wb");
	if (!out_fp){
		printf ("Error creating output file\n");
		exit(1);
	}

	// Allocate memory for input and output buffers 

	unsigned char *in_buf = (size_t *) malloc(BUFSIZE);
	unsigned char *out_buf = (size_t *) malloc(BUFSIZE);


	size_t * in_buf_len; 
	size_t * out_buf_len;


	// Encrypt input file with public key and write to output file 

	while ((in_buf_len = fread(in_buf, 1, BUFSIZE, in_fp)) > 0){
    	out_buf_len = EVP_PKEY_encrypt(public_key, out_buf, in_buf, in_buf_len, RSA_PKCS1_OAEP_PADDING);
    	if (out_buf_len < 0) {   // Error occurs on this line
        	printf("Error encrypting data\n");
        	exit(1);
    	}
    	fwrite(out_buf, 1, out_buf_len, out_fp);
	}
    
	// Decrypt output file with private key and write to output file 

	while ((out_buf_len = fread(out_buf, 1, BUFSIZE, in_fp)) > 0){
    	in_buf_len = EVP_PKEY_decrypt(private_key, in_buf, out_buf, out_buf_len, RSA_PKCS1_OAEP_PADDING);
    	if (in_buf_len < 0) {
        	printf("Error decrypting data\n");
        	exit(1);
    	}
    	fwrite(in_buf, 1, in_buf_len, out_fp);
	}	


	// Free memory and close file handles
	free(in_buf);
	free(out_buf);

	EVP_PKEY_free(public_key);
	EVP_PKEY_free(private_key);


	fclose(in_fp);
	fclose(out_fp);


	return 0;
}