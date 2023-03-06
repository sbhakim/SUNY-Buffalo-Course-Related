
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

# Set the chunk size (in bytes)
chunk_size = 1024 * 1024  # 1 MB

# Hash the file using SHA-256
hash = hashlib.sha256()

with open("file_1_MB.txt", "rb") as f:
    while True:
        # Read a chunk of data
        chunk = f.read(chunk_size)
        if not chunk:
            # End of file
            break
        # Update the hash object with the chunk
        hash.update(chunk)

# Get the digest of the hash
digest = hash.digest()

# Load the DSA private key
with open("dsaprivkey.pem", "rb") as f:
    priv_key = load_pem_private_key(f.read(), password=None)

# Sign the hash using DSA
signature = priv_key.sign(digest, hashes.SHA256())

# Save the signature to a file
with open("file_1_MB.sig", "wb") as f:
    f.write(signature)

# Load the DSA public key
with open("dsapubkey.pem", "rb") as f:
    pub_key = load_pem_public_key(f.read())

# Verify the signature
with open("file_1_MB.sig", "rb") as f:
    signature = f.read()

if not isinstance(signature, bytes):
    raise TypeError("Signature must be bytes")

if not isinstance(pub_key, dsa.DSAPublicKey):
    raise TypeError("Key must be a DSA public key")

# Decode the signature and verify it
r, s = decode_dss_signature(signature)
pub_key.verify(signature, digest, hashes.SHA256())
print("Signature is valid.")



