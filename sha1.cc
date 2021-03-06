#include <stdint.h>
#include <array>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "sha1.h"

namespace {
  inline uint32_t f(unsigned int t, uint32_t b, uint32_t c, uint32_t d) {
    if (t <= 19)
      return (b & c) | ((~b) & d);
    else if (t <= 39)
      return b ^ c ^ d;
    else if (t <= 59)
      return (b & c) | (b & d) | (c & d);
    else if (t <= 79)
      return b ^ c ^ d;
  }

  inline uint32_t K(unsigned int t) {
    if (t <= 19)
      return 0x5A827999;
    else if (t <= 39)
      return 0x6ED9EBA1;
    else if (t <= 59)
      return 0x8F1BBCDC;
    else if (t <= 79)
      return 0xCA62C1D6;
  }
  
  inline uint32_t circularShift(unsigned int n, uint32_t X) {
    return (X << n) | (X >> (32 - n));
  }
}

const unsigned int Sha1::BLOCK_SIZE = 512 / 8;

void Sha1::input(std::string message) {
  input( (uint8_t *)message.c_str(), message.size());
}

void Sha1::input(std::vector<uint8_t> &message) {
  input( message.data(), message.size());
}

void Sha1::input(uint8_t *message, size_t len) {
  // create paddedMessage
  int n = len / BLOCK_SIZE;
  int rem = BLOCK_SIZE - len % BLOCK_SIZE;
  int size = (n + 1) * BLOCK_SIZE;

  // less space
  if (rem <= 8) {
    size += BLOCK_SIZE;
  }
  
  m_paddedMessage.resize(size);
  std::fill(m_paddedMessage.begin(), m_paddedMessage.end(), 0);
  std::copy(message, message + len, m_paddedMessage.begin());

  if (rem > 0) {
    m_paddedMessage[len] |= 0x80;

    uint64_t message_len = len * 8L;
    uint32_t high = (message_len >> 32);
    uint32_t low  = (message_len & 0x00000000ffffffffL);
    //m_paddedMessage[m_paddedMessage.size() - 1] |= len * 8;
    m_paddedMessage[m_paddedMessage.size() - 8] = high >> 24;
    m_paddedMessage[m_paddedMessage.size() - 7] = high >> 16;
    m_paddedMessage[m_paddedMessage.size() - 6] = high >> 8;
    m_paddedMessage[m_paddedMessage.size() - 5] = high;

    m_paddedMessage[m_paddedMessage.size() - 4] = low >> 24;
    m_paddedMessage[m_paddedMessage.size() - 3] = low >> 16;
    m_paddedMessage[m_paddedMessage.size() - 2] = low >> 8;
    m_paddedMessage[m_paddedMessage.size() - 1] = low;
  }
}

void Sha1::result(Sha1Result *result) {
  uint32_t w[80] = {};
  uint32_t A, B, C, D, E;
  uint32_t H0, H1, H2, H3, H4;
  uint32_t temp;
  std::array<uint32_t, 5> H;

  H[0] = 0x67452301;
  H[1] = 0xEFCDAB89;
  H[2] = 0x98BADCFE;
  H[3] = 0x10325476;
  H[4] = 0xC3D2E1F0;

  for (int i = 0; i < m_paddedMessage.size() / BLOCK_SIZE; i++) {
    int offset = i * BLOCK_SIZE;

    for (int t = 0; t < 16; t++) {
      w[t]  = this->m_paddedMessage[offset + t * 4 + 0] << 24;
      w[t] |= this->m_paddedMessage[offset + t * 4 + 1] << 16;
      w[t] |= this->m_paddedMessage[offset + t * 4 + 2] << 8;
      w[t] |= this->m_paddedMessage[offset + t * 4 + 3];
    }

    for (int t = 16; t <= 79; t++) {
      w[t] = circularShift(1, w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]);
    }

    A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];

    for (int t = 0; t <= 79; t++) {
      temp = circularShift(5, A) + f(t, B, C, D) + E + w[t] + K(t);
      E = D; D = C; C = circularShift(30, B); B = A; A = temp;
    }
    
    H[0] = H[0] + A; H[1] = H[1] + B; H[2] = H[2] + C;
    H[3] = H[3] + D; H[4] = H[4] + E;
  }
  
  result->setResult(H);
}

void Sha1::reset() {
  m_paddedMessage.clear();
}

void Sha1Result::setResult(const std::array<uint32_t, 5> &result) {
  m_result = result;
}

std::vector<uint8_t> Sha1Result::toBytes() {
  std::vector<uint8_t> result;

  for (int i = 0; i < m_result.size(); ++i) {
    uint32_t w = m_result[i];
    uint8_t b0 = w >> 6;
    uint8_t b1 = w >> 4;
    uint8_t b2 = w >> 2;
    uint8_t b3 = w;

    result.push_back(b0); result.push_back(b1);
    result.push_back(b2); result.push_back(b3);
  }

  return result;
}

std::string Sha1Result::toString() {
  std::stringstream ss;

  for (int i = 0; i < m_result.size(); ++i) {
    ss << std::hex << std::setfill('0') << std::setw(8) << m_result[i];
  }

  return ss.str();
}  
