#include <stdint.h>
#include <string>
#include <vector>

class Sha1Result;

class Sha1 {
public:
  static const unsigned int BLOCK_SIZE;
  
  Sha1();
  ~Sha1();

  void input(std::string message);
  void input(std::vector<uint8_t> &message);
  void input(uint8_t *message, size_t len);
  
  void result(Sha1Result *result);
  Sha1Result result();
  
private:
  std::vector<uint8_t> m_PaddedMessage;
};

class Sha1Result {
public:
  void SetResult(const std::vector<uint32_t> &result);

  std::string ToString();
  
private:
  std::vector<uint32_t> m_Result;
};
