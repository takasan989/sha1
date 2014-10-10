#include <stdint.h>
#include <vector>
#include <memory>
#include "sha1.h"

class Sha1Result;

class HmacSha1 {
public:
  void input(uint8_t *key, uint8_t *message);
  void result(Sha1Result *result);
  
private:
  std::vector<uint8_t> m_key;
  std::vector<uint8_t> m_message;
};
