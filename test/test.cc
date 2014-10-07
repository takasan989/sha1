#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../sha1.h"
#include <iostream>

#define EXPECT "f7ff9e8b7bb2e09b70935a5d785e0cc5d9d0abf0"

TEST(Sha1Test, sha1test) {
  Sha1 sha;
  Sha1Result result;
  char buf[] = "Hello";

  sha.input( (uint8_t *)buf, strlen(buf));
  sha.result(&result);

  ASSERT_STREQ(EXPECT, result.ToString().c_str());
}
