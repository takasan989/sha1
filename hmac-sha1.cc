#include <stdint.h>
#include <vector>
#include "hmac-sha1.h"
#include "sha1.h"
using namespace std;

namespace {
  vector<uint8_t> exclusiveOr(vector<uint8_t> &a, vector<uint8_t> &b) {
    vector<uint8_t> result;

    for (int i = 0; i < a.size(); ++i) {
      result.push_back(a[i] ^ b[i]);
    }
    return result;
  }

  vector<uint8_t> concat(vector<uint8_t> &a, vector<uint8_t> &b) {
    vector<uint8_t> result = a;
    result.insert(result.end(), b.begin(), b.end());
    return result;
  }
}

void HmacSha1::input(vector<uint8_t> &key, vector<uint8_t> &message) {
  vector<uint8_t> ipad(Sha1::BLOCK_SIZE, 0x36);
  vector<uint8_t> opad(Sha1::BLOCK_SIZE, 0x5c);
  vector<uint8_t> processedKey;
  
  if (key_len > Sha1::BLOCK_SIZE) {
    Sha1 sha1;
    Sha1Result result;

    sha1.input(key, keyLen);
    sha1.result(&result);
    processedKey = result.toBytes();
  } else {
    processedKey = key;
    // padding
    for (int i = 0; i < (Sha1::BLOCK_SIZE - key.size()); ++i)
      processedKey.push_back(0x00);
  }

  m_key = processedKey;
  m_message = message;
}
