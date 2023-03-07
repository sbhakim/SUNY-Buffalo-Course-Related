#! /usr/bin/python3


import time
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

class RSAEncryptor:
    def __init__(self):
        # Generate RSA key pair
        self.key = RSA.generate(2048)
        
        # Save private key to file
        with open('private_key.pem', 'wb') as f:
            f.write(self.key.export_key('PEM'))
        
        # Save public key to file
        with open('public_key.pem', 'wb') as f:
            f.write(self.key.publickey().export_key('PEM'))
        
        # Load public key from file
        with open('public_key.pem', 'rb') as f:
            self.public_key = RSA.import_key(f.read())
    
    def encrypt(self, message):
        start_time = time.time()
        # Encrypt message using public key
        cipher = PKCS1_OAEP.new(self.public_key)
        ciphertext = cipher.encrypt(message)
        end_time = time.time()
        
        encryption_time = end_time - start_time
        encryption_speed = encryption_time / len(message) * 1000

        print('Encryption time: {:.2f} ms'.format(encryption_time * 1000))
        print('Encryption speed per byte: {:.5f} ms/byte'.format(encryption_speed))

        
        return ciphertext
    
    def decrypt(self, ciphertext):
        # Load private key from file
        with open('private_key.pem', 'rb') as f:
            private_key = RSA.import_key(f.read())
        
        start_time = time.time()
        # Decrypt ciphertext using private key
        cipher = PKCS1_OAEP.new(private_key)
        plaintext = cipher.decrypt(ciphertext) 
        end_time = time.time()
        
        decryption_time = end_time - start_time
        decryption_speed = decryption_time / len(plaintext) * 1000

        print('Decryption time: {:.2f} ms'.format(decryption_time * 1000))
        print('Decryption speed per byte: {:.5f} ms/byte'.format(decryption_speed))
        
      
        return plaintext

if __name__ == '__main__':
    # Read file contents
    with open('short_file.txt', 'rb') as f:
        message = f.read()
        
    encryptor = RSAEncryptor()
    ciphertext = encryptor.encrypt(message)
    plaintext = encryptor.decrypt(ciphertext)
    
    # Print results
    print('Original message:', message)




