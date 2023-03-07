
'''
This program takes the names of two files as command line arguments and computes 
the SHA-256 hash value of each file. It then uses the OpenSSL library to generate
 a 2048-bit DSA key pair with 224-bit exponent size. The program signs 
 the hash values of each file using the private key and verifies the signatures 
 using the corresponding public key. The program prints whether each signature 
 is valid or not. 
'''

#!/usr/bin/env python3

import hashlib
import os
import time
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import dsa
from cryptography.hazmat.primitives.asymmetric.utils import (
    encode_dss_signature,
    decode_dss_signature,
)
from cryptography.hazmat.primitives.serialization import (
    load_pem_private_key,
    load_pem_public_key,
)
import subprocess

# Generate DSA keys
start_time = time.perf_counter()

subprocess.run(['openssl', 'dsaparam', '-out', 'dsaparam.pem', '2048'], check=True)
subprocess.run(['openssl', 'gendsa', '-out', 'dsaprivkey.pem', 'dsaparam.pem'], check=True)
subprocess.run(['openssl', 'dsa', '-in', 'dsaprivkey.pem', '-pubout', '-out', 'dsapubkey.pem'], check=True)

key_gen_time = (time.perf_counter() - start_time) * 1000

print(f"DSA key generation took {key_gen_time:.2f} milliseconds")

# Read the file to be signed
with open("file_1_MB.txt", "rb") as f:
    data = f.read()

# Hash the file using SHA-256
hash = hashlib.sha256(data).digest()

# Load the DSA private key
with open("dsaprivkey.pem", "rb") as f:
    priv_key = load_pem_private_key(f.read(), password=None)

# Sign the hash using DSA
start_time = time.perf_counter()

signature = priv_key.sign(hash, hashes.SHA256())

sign_time = (time.perf_counter() - start_time) * 1000

print(f"Time to produce signature (1 MB file): {sign_time:.2f} milliseconds")

# Save the signature to a file
with open("file_1_MB.sig", "wb") as f:
    f.write(signature)

signature_size = os.path.getsize("file_1_MB.sig")
per_byte_time = sign_time / signature_size
print(f"Per-byte time during signing (1 MB file): {per_byte_time:.6f} milliseconds/byte")

# Load the DSA public key
with open("dsapubkey.pem", "rb") as f:
    pub_key = load_pem_public_key(f.read())

# Verify the signature
start_time = time.perf_counter()

with open("file_1_MB.sig", "rb") as f:
    signature = f.read()

if not isinstance(signature, bytes):
    raise TypeError("Signature must be bytes")

if not isinstance(pub_key, dsa.DSAPublicKey):
    raise TypeError("Key must be a DSA public key")

# Decode the signature and verify it
r, s = decode_dss_signature(signature)

start_verifying = time.perf_counter()
pub_key.verify(signature, hash, hashes.SHA256())
verifying_time = (time.perf_counter() - start_verifying) * 1000

print("Signature is valid.")
print(f"Time to verify signature (1 MB file): {verifying_time:.2f} milliseconds")

signature_size = os.path.getsize("file_1_MB.sig")
per_byte_time = verifying_time / signature_size
print(f"Per-byte time during signature verification (1 MB file): {per_byte_time:.6f} milliseconds/byte")


#######################################################
# Set the size of the diamond (odd number)
size = 5

# Print diamond
for i in range(1, size + 1):
    if i % 2 != 0:
        print(' ' * ((size - i) // 2), end='')
        print('*' * i)
for i in range(size - 2, 0, -1):
    if i % 2 != 0:
        print(' ' * ((size - i) // 2), end='')
        print('*' * i)
###########################################################

# Read the file to be signed
with open("file_10_MB.txt", "rb") as f:
    data = f.read()

# Hash the file using SHA-256
hash = hashlib.sha256(data).digest()

# Load the DSA private key
with open("dsaprivkey.pem", "rb") as f:
    priv_key = load_pem_private_key(f.read(), password=None)

# Sign the hash using DSA
start_time = time.perf_counter()

signature = priv_key.sign(hash, hashes.SHA256())

sign_time = (time.perf_counter() - start_time) * 1000

print(f"Time to produce signature (10 MB file): {sign_time:.2f} milliseconds")

# Save the signature to a file
with open("file_10_MB.sig", "wb") as f:
    f.write(signature)

signature_size = os.path.getsize("file_10_MB.sig")
per_byte_time = sign_time / signature_size
print(f"Per-byte time during signing (10 MB file): {per_byte_time:.6f} milliseconds/byte")

# Load the DSA public key
with open("dsapubkey.pem", "rb") as f:
    pub_key = load_pem_public_key(f.read())

# Verify the signature
start_time = time.perf_counter()

with open("file_10_MB.sig", "rb") as f:
    signature = f.read()

if not isinstance(signature, bytes):
    raise TypeError("Signature must be bytes")

if not isinstance(pub_key, dsa.DSAPublicKey):
    raise TypeError("Key must be a DSA public key")

# Decode the signature and verify it
r, s = decode_dss_signature(signature)

start_verifying = time.perf_counter()
pub_key.verify(signature, hash, hashes.SHA256())
verifying_time = (time.perf_counter() - start_verifying) * 1000

print("Signature is valid.")
print(f"Time to verify signature (10 MB file): {verifying_time:.2f} milliseconds")

signature_size = os.path.getsize("file_10_MB.sig")
per_byte_time = verifying_time / signature_size
print(f"Per-byte time during signature verification (10 MB file): {per_byte_time:.6f} milliseconds/byte")



