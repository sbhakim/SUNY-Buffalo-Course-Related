#!/bin/sh

openssl dsaparam -out dsaparam.pem 2048
openssl gendsa -out dsaprivkey.pem dsaparam.pem
openssl dsa -in dsaprivkey.pem -pubout -out dsapubkey.pem

