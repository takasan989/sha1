#include <stdint.h>
#include <vector>
#include <memory>
#include "sha1.h"

class Sha1Result;

class HmacSha1 {
public:
  void Input(uint8_t *key, uint8_t *message);
  void Result(Sha1Result *result);
  
private:
  std::vector<uint8_t> m_Key;
  std::vector<uint8_t> m_Message;
};
