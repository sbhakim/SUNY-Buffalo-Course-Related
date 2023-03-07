#! /usr/bin/python3





import time
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

start_time = time.time()

# Generate RSA key pair
key = RSA.generate(2048)

end_time = time.time()
key_gen_time = (end_time - start_time) * 1000  # Convert to milliseconds

# Save private key to file
with open('private_key.pem', 'wb') as f:
    f.write(key.export_key('PEM'))

# Save public key to file
with open('public_key.pem', 'wb') as f:
    f.write(key.publickey().export_key('PEM'))

# Load public key from file
with open('public_key.pem', 'rb') as f:
    public_key = RSA.import_key(f.read())

# Read file contents
with open('short_file.txt', 'rb') as f:
    message = f.read()

# Encrypt message using public key
cipher = PKCS1_OAEP.new(public_key)
ciphertext = cipher.encrypt(message)

# Load private key from file
with open('private_key.pem', 'rb') as f:
    private_key = RSA.import_key(f.read())

# Decrypt ciphertext using private key
cipher = PKCS1_OAEP.new(private_key)
plaintext = cipher.decrypt(ciphertext)

# Print results
print('Original message:', message)
print(" " * 10)
print('Encrypted message:', ciphertext)
print(" " * 10)
print('Decrypted message:', plaintext)
print(" " * 10)
print('Key generation time (ms):', key_gen_time)


