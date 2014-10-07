#include <stdint.h>

namespace std {
  class vector<T>;
}
class MessageBlock;

class Sha1 {
public:
  Sha1();
  ~Sha1();

  void process(uint32_t result[5]);
  void padding();
  void input(uint8_t *message, size_t len);
  
private:
  uint8_t *m_message;
  size_t m_messageLen;
  std::vector<MessageBlock> *m_MessageBlocks;
};

class MessageBlock {
public:
  MessageBlock(const uint8_t *data, size_t size);
  
private:
  uint8_t m_data[64];
}
