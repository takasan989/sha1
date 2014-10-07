#include <stdint.h>
#include <string>
#include <vector>

class Sha1Result;

class Sha1 {
public:
  Sha1();
  ~Sha1();

  void result(Sha1Result *result);
  Sha1Result result();
  void padding();
  void input(uint8_t *message, size_t len);
  
private:
  uint8_t *m_Message;
  size_t m_MessageLen;
  std::vector<uint8_t> m_PaddedMessage;
};

class Sha1Result {
public:
  void SetResult(const std::vector<uint32_t> &result);

  std::string ToString();
  
private:
  std::vector<uint32_t> m_Result;
};
