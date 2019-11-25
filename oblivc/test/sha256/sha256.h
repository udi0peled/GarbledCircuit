#pragma once

typedef unsigned char byte;
typedef unsigned int word;

void compute_sha256(void*arg);
void sha256_test(void*arg);
void compute_process_raw(void* args);

void printHexBytes(const byte* src, unsigned len);
unsigned readHexBytes(byte* dest,unsigned* d_len,const char* src,unsigned s_len);

// SHA256 outputs a 32 byte digest
#define SHA256_DIGEST_SIZE 32      

typedef struct {
  byte* input_share;
  unsigned int input_len;
  byte msg_digest[SHA256_DIGEST_SIZE];
} protocolIO;
