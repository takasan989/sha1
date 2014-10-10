#include <stdint.h>
#include "hmac-sha1.h"
#include "sha1.h"

void HmacSha1::Input(uint8_t *key, size_t key_len,
                     uint8_t *message, size_t message_len) {
  if (key_len > Sha1::BLOCK_SIZE) {
    Sha1 sha1;
    Sha1Result result;
  }
}
