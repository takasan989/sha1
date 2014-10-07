#include <gtest/gtest.h>
#include <string.h>
#include <vector>
#include "../sha1.h"

TEST(t, t) {
  Sha1 sha;
  uint32_t result[5];
  char buf[] = "Hello";

  //sha.input( (uint8_t *)buf, strlen(buf));
  //sha.process(result);
}
