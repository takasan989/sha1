#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "sha1.h"

#include <stdio.h>

#define BIT 512
#define BYTE (BIT / 8)

namespace {
  void print(uint8_t *buf, size_t len) {

    for (int i = 0; i < len; i++) {
      printf("%02X", buf[i]);
    
      if ((i + 1) % 16 == 0) printf("\n");
      else if ((i + 1) % 4 == 0) printf(" ");
    }
  }

  void print32(uint32_t *buf, size_t len) {
    for (int i = 0; i < len; i++) {
      printf("%08X ", buf[i]);
    
      if ((i + 1) % 4 == 0) printf("\n");
    }
  }

  uint32_t f(unsigned int t, uint32_t b, uint32_t c, uint32_t d) {
    if (t <= 19)
      return (b & c) | ((~b) & d);
    else if (t <= 39)
      return b ^ c ^ d;
    else if (t <= 59)
      return (b & c) | (b & d) | (c & d);
    else if (t <= 79)
      return b ^ c ^ d;
  }

  uint32_t k(unsigned int t) {
    if (t <= 19)
      return 0x5A827999;
    else if (t <= 39)
      return 0x6ED9EBA1;
    else if (t <= 59)
      return 0x8F1BBCDC;
    else if (t <= 79)
      return 0xCA62C1D6;
  }

  uint32_t S(unsigned int n, uint32_t X) {
    return (X << n) | (X >> (32 - n));
  }
}

Sha1::Sha1() {
}

Sha1::~Sha1() {
  delete[] this->m_paddedMessage;
}

void Sha1::input(uint8_t *message, size_t len) {
  this->m_message = message;
  this->m_messageLen = len;
  printf("%d\n", len);
}

void Sha1::process(uint32_t result[5]) {
  /*
  this->padding();

  uint32_t w[80] = {};
  uint32_t A, B, C, D, E;
  uint32_t H0, H1, H2, H3, H4;
  uint32_t temp;

  H0 = 0x67452301;
  H1 = 0xEFCDAB89;
  H2 = 0x98BADCFE;
  H3 = 0x10325476;
  H4 = 0xC3D2E1F0;

  for (int i = 0; i < this->m_paddedMessageLen / BYTE; i++) {
    int offset = i * BYTE;

    for (int t = 0; t < 16; t++) {
      w[t]  = this->m_paddedMessage[offset * BYTE + t * 4 + 0] << 24;
      w[t] |= this->m_paddedMessage[offset * BYTE + t * 4 + 1] << 16;
      w[t] |= this->m_paddedMessage[offset * BYTE + t * 4 + 2] << 8;
      w[t] |= this->m_paddedMessage[offset * BYTE + t * 4 + 3];
    }

    print32(w, 80);

    for (int t = 16; t <= 79; t++) {
      w[t] = S(1, w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]);
    }

    A = H0; B = H1; C = H2; D = H3; E = H4;

    for (int t = 0; t <= 79; t++) {
      temp = S(5, A) + f(t, B, C, D) + E + w[t] + k(t);
      E = D; D = C; C = S(30, B); B = A; A = temp;
    }
  }
  
  H0 = H0 + A; H1 = H1 + B; H2 = H2 + C; H3 = H3 + D; H4 = H4 + E;
  
  result[0] = H0; result[1] = H1; result[2] = H2;
  result[3] = H3; result[4] = H4;
  */
}

void Sha1::padding() {
  /*
  int n = this->m_messageLen / BYTE;
  int rem = BYTE - this->m_messageLen % BYTE;
  int size = (n + 1) * BYTE;

  this->m_paddedMessage = new uint8_t[size];
  this->m_paddedMessageLen = size;
  
  memcpy(this->m_paddedMessage, this->m_message, this->m_messageLen);

  if (rem > 0) {
    memset(&(this->m_paddedMessage[this->m_messageLen]), 0x00, rem);
    this->m_paddedMessage[this->m_messageLen] = 0x80;
    this->m_paddedMessage[this->m_paddedMessageLen - 1]
      |= this->m_messageLen * 8;
  }
  //print(this->m_paddedMessage, this->m_paddedMessageLen);
  */
}

MessageBlock::MessageBlock(const uint8_t data, size_t size = 64) {
  for (int i = 0; i < size; ++i) {
    m_data[i] = data[i];
  }
}
