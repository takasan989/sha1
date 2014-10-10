#include <stdint.h>
#include <string>
#include <array>
#include <vector>

class Sha1Result;

class Sha1 {
public:
  static const unsigned int BLOCK_SIZE;

  void input(std::string message);
  void input(std::vector<uint8_t> &message);
  void input(uint8_t *message, size_t len);
  
  void result(Sha1Result *result);

  void reset();
  
private:
  std::vector<uint8_t> m_paddedMessage;
};

class Sha1Result {
public:
  void setResult(const std::array<uint32_t, 5> &result);

  std::vector<uint8_t> toBytes();
  std::string toString();
  
private:
  std::array<uint32_t, 5> m_result;
};
