
/*
The program reads a public key and a private key from their respective files and uses them to encrypt and 
decrypt data from an input file. The encrypted data is written to an output file, which is then decrypted 
using the private key and written to another output file. The encryption and decryption is performed using 
RSA_PKCS1_OAEP_PADDING algorithm. The program takes command line arguments specifying the input and output 
file names, as well as the public and private key file names.


$ ./rsa_encrypt public_key.pem private_key.pem random_ascii.txt  random_ascii_encrypted.bin

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>


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


	// Read public key from file 
	FILE *pub_fp = fopen(public_key_file, "rb"); 
	if (!pub_fp) {
		printf("Error opening public key file \n");
		exit(1);
	}

	RSA *public_key = PEM_read_RSA_PUBKEY(pub_fp, NULL, NULL, NULL);
	fclose (pub_fp); 

	// Read private key from file 

	FILE *priv_fp = fopen(private_key_file, "rb");
	if (!priv_fp) {
		printf ("Error opening private key file\n");
		exit(1);
	}

	RSA *private_key = PEM_read_RSAPrivateKey(priv_fp, NULL, NULL, NULL);
	fclose(priv_fp); 

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

	unsigned char *in_buf = (unsigned char *) malloc(BUFSIZE);
	unsigned char *out_buf = (unsigned char *) malloc(BUFSIZE);


	int in_buf_len, out_buf_len;


	// Encrypt input file with public key and write to output file 

	while ((in_buf_len = fread(in_buf, 1, BUFSIZE, in_fp)) > 0){
		out_buf_len = RSA_public_encrypt (in_buf_len, in_buf, out_buf,public_key, RSA_PKCS1_OAEP_PADDING);
		if(out_buf_len == -1){
			printf("Error encypting input file\n");
			exit(1);
		}
		fwrite (out_buf, 1, out_buf_len, out_fp);
	}

	// Decrypt output file with private key and write to output file 
	while ((out_buf_len = fread(out_buf, 1, BUFSIZE, out_fp))>0){
		in_buf_len = RSA_private_decrypt (out_buf_len, out_buf, in_buf, private_key, RSA_PKCS1_OAEP_PADDING);
		if (in_buf_len == -1){
			printf ("Error decrypting output file \n");
			exit(1);
		}
		fwrite(in_buf, 1, in_buf_len, in_fp);
	}

	// Free memory and close file handles
	free(in_buf);
	free(out_buf);

	RSA_free(public_key);
	RSA_free(private_key);


	fclose(in_fp);
	fclose(out_fp);


	return 0;
}