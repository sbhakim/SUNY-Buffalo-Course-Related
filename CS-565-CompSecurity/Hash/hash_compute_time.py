#!/usr/bin/env python3
import sys
import hashlib
import time 

BUFSIZE = 1024

if len(sys.argv) < 3:
    print(f"Usage: {sys.argv[0]} file1 file2")
    sys.exit(1)

file1 = sys.argv[1]
file2 = sys.argv[2]

# Compute hash of file1 with SHA-256
start_time = time.time()
with open(file1, "rb") as f:
    sha256 = hashlib.sha256()
    while True:
        data = f.read(BUFSIZE)
        if not data:
            break
        sha256.update(data)
    print(f"{file1} SHA-256 hash: {sha256.hexdigest()}")
end_time = time.time()
print(f"Time taken to compute SHA-256 hash of {file1}: {end_time - start_time} seconds")

# Compute hash of file1 with SHA-512
start_time = time.time()
with open(file1, "rb") as f:
    sha512 = hashlib.sha512()
    while True:
        data = f.read(BUFSIZE)
        if not data:
            break
        sha512.update(data)
    print(f"{file1} SHA-512 hash: {sha512.hexdigest()}")
end_time = time.time()
print(f"Time taken to compute SHA-512 hash of {file1}: {end_time - start_time} seconds")

# Compute hash of file2 with SHA-256
start_time = time.time()
with open(file2, "rb") as f:
    sha256 = hashlib.sha256()
    while True:
        data = f.read(BUFSIZE)
        if not data:
            break
        sha256.update(data)
    print(f"{file2} SHA-256 hash: {sha256.hexdigest()}")
end_time = time.time()
print(f"Time taken to compute SHA-256 hash of {file2}: {end_time - start_time} seconds")

# Compute hash of file2 with SHA-512
start_time = time.time()
with open(file2, "rb") as f:
    sha512 = hashlib.sha512()
    while True:
        data = f.read(BUFSIZE)
        if not data:
            break
        sha512.update(data)
    print(f"{file2} SHA-512 hash: {sha512.hexdigest()}")
end_time = time.time()
print(f"Time taken to compute SHA-512 hash of {file2}: {end_time - start_time} seconds")

