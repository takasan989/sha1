#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdin.h>
#include <iostream>
#include <fstream>
#include "../sha1.h"
using namespace std;

vector<string> string_data {
  "Hello",
  "abc",
  "YJf0PFe2X6MGHkfAnzhcQeWuiQpzOzjEacC8ABgUDwtclLKovY17TlwJQqjzUIc9eNA4tBQN72tkwPZ40BgGiDVLgUNjmUCEyMwM",
  "sMXJAwqmn3Jfx35GxqvD8rAuPoYrlEIZh2Iu1zO3qLphvtWoF6lQCWJo8SbbVM7f",
  "ibpt5gvuMJOt8B25I2mJlEcxuxua1YrDBcokPS9Fn0TqrEleTKCqETZDP0z9HZzzj6Morv5SSrEPGxN4o1guQoLyZDHNmSqVc2bWqv8fDxjn5SQtBt3AtJjJOLseWYJhYaxnJbckOkDl724m973ViGiiBg2I9kUkNLluNF6C2fMJ4hwtylq1tYvsZptkX9NtYEMqPiHixlQfgTsvvKxBpNlMjZM7RjE9BjM4b5T2ugq8ssTOvyJ54JrOF81NoJCY"
};

vector<string> string_expects {
  "f7ff9e8b7bb2e09b70935a5d785e0cc5d9d0abf0",
  "a9993e364706816aba3e25717850c26c9cd0d89d",
  "c00b9f45b8c48595f84b9ab16ff4ccde20b261be",
  "70438bed54fa9a0db145f6076415009ad611ff37",
  "0319594aef63ddd4c7c3c807a35efae3914c891d"
};

vector<string> file_data {
  
};

void ReadFile(string file, vector<uint8_t> &result) {
  uint8_t c;
  ifstream fin(file, ios::in | ios::binary);

  while (!fin.eof()) {
    fin.read(&c, sizeof(uint8_t));
    result.push_back(c);
  }
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

    ReadFile(file_data[i], bytes);
    
    sha1.input(bytes);
    sha1.result(&result);

    EXPECT_STREQ(file_expects[i].c_str(), result.ToString().c_str());
  }
}
