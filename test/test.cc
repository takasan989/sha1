#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include "../sha1.h"
#include "test.h"
using namespace std;

vector<string> string_data {
  "H",
  "abc",
  "YJf0PFe2X6MGHkfAnzhcQeWuiQpzOzjEacC8ABgUDwtclLKovY17TlwJQqjzUIc9eNA4tBQN72tkwPZ40BgGiDVLgUNjmUCEyMwM",
  "sMXJAwqmn3Jfx35GxqvD8rAuPoYrlEIZh2Iu1zO3qLphvtWoF6lQCWJo8SbbVM7f",
  "o938rEp3GX0fxS7GcwuQvr6VIAph3gpEAUChDoDPvtLvqAX7PkbSexeOX4Z9HOLTj2zulwDolBMaX4hNAUALbvCRYkKANXvrzLkWfBE7BNiPz35vSjv19n6GORSlE80",
  "ibpt5gvuMJOt8B25I2mJlEcxuxua1YrDBcokPS9Fn0TqrEleTKCqETZDP0z9HZzzj6Morv5SSrEPGxN4o1guQoLyZDHNmSqVc2bWqv8fDxjn5SQtBt3AtJjJOLseWYJhYaxnJbckOkDl724m973ViGiiBg2I9kUkNLluNF6C2fMJ4hwtylq1tYvsZptkX9NtYEMqPiHixlQfgTsvvKxBpNlMjZM7RjE9BjM4b5T2ugq8ssTOvyJ54JrOF81NoJCY",
  "iheCuogpusK5nWXuECyOuOx08HlzaTrN5Lo5NqwzvgLwFjJ6bygjuSIwtjOnWBwXMlFr3aeg3LvpAM6njBfnLCzG2D8G1hWxkWbgFggM6S3MjeSS9LVW0im0",
  "yqy5xnF0bQGUyFZ2gnnxqZ1OZTKfFQeoJ3bmHWa2Mg4f18nmCaRvWbwu96Fl3Jiz1OacNslVmFWc5znrrFshilPqRUpsZGEuVGqogmc8j2joN7icKen0fsl",
};

vector<string> string_expects {
  "f7ff9e8b7bb2e09b70935a5d785e0cc5d9d0abf0",
  "a9993e364706816aba3e25717850c26c9cd0d89d",
  "c00b9f45b8c48595f84b9ab16ff4ccde20b261be",
  "70438bed54fa9a0db145f6076415009ad611ff37",
  "2d18dbba5c91433aabdc2b3c1556c159bcf5d411",
  "0319594aef63ddd4c7c3c807a35efae3914c891d",
  "1b1a74008d83336643745f0d79e450cbf8f08d62",
  "366504d506dd3e6d7d51a7a2a00783b30467ccce",
};

vector<string> file_data {
  "res/test.cc",
  "res/random",
  "res/zero",
};

vector<string> file_expects {
  "fccff41002c0cc67031f5349f35f57aa6f9da983",
  "509a52a261c600cd679386e025d0b5b45483034b",
  "b110a88a11436b215220486c1081dec2fb0f389a",
};

int ReadFile(string file, vector<uint8_t> &result) {
  string path = TEST_ROOT + file;
  int c;
  FILE *fp;
  
  fp = fopen(path.c_str(), "rb");

  if (fp == NULL) return -1;

  while ((c = fgetc(fp)) != EOF) {
    result.push_back( (uint8_t)c);
  }

  fclose(fp);
}

TEST(Sha1Test, StringTest) {
  for (int i = 0; i < string_data.size(); ++i) {
    Sha1 sha1;
    Sha1Result result;
    sha1.input(string_data[i]);
    sha1.result(&result);
    
    EXPECT_STREQ(string_expects[i].c_str(), result.ToString().c_str());
  }
}

TEST(Sha1Test, FileTest) {
  for (int i = 0; i < file_data.size(); ++i) {
    Sha1 sha1;
    Sha1Result result;
    vector<uint8_t> bytes;

    if (ReadFile(file_data[i], bytes) == -1) {
      cout << "[!!!!!!!!!!] " << file_data[i] << " is not exists." << endl;
      continue;
    }

    sha1.input(bytes);
    sha1.result(&result);

    EXPECT_STREQ(file_expects[i].c_str(), result.ToString().c_str());
  }
}
