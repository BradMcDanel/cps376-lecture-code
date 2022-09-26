#include <iostream>
#include <vector>

#include "random_string.h"

#define STR_LENGTH 8388608

int find_string(std::string &str, std::string &substr) {
  // TODO: Implement find_string
  return -1;
}

int main() {
  std::string str = random_string(STR_LENGTH);
  std::string substr = "pizza";

  int idx = find_string(str, substr);
  std::cout << "Found " << substr << " at index " << idx << std::endl;

  return 0;
}
