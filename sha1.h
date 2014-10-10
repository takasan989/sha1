#include <stdint.h>
#include <string>
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
  std::vector<uint8_t> m_padded_message;
};

class Sha1Result {
public:
  void set_result(const std::vector<uint32_t> &result);

  std::string to_string();
  
private:
  std::vector<uint32_t> m_result;
};
