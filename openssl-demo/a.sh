#! /bin/sh

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/z/resource/openssl

/home/z/resource/openssl/apps/openssl enc -aes-256-cbc -in ./makefile -nosalt -pass file:./key/sym.key -p -out out-enc
