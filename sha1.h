#include <stdlib.h>
#include <stdint.h>

class Sha1 {
public:
  Sha1();
  ~Sha1();

  void process(uint32_t result[5]);
  void padding();
  void input(uint8_t *message, size_t len);
 
  uint8_t *m_message;
  size_t m_messageLen;
  uint8_t *m_paddedMessage;
  size_t m_paddedMessageLen;
};
