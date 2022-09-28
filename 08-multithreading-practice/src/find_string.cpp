#include <iostream>
#include <vector>

#include "random_string.h"

#define STR_LENGTH 8388608

int find_string(std::string &str, std::string &substr) {
  for (size_t i = 0; i < str.size() - substr.size() + 1; i++) {
    for (size_t j = 0; j < substr.size(); j++) {
      if (str[i + j] != substr[j]) {
        break;
      }
      if (j == substr.size() - 1) {
        return i;
      }
    }
  }
  return -1;
}

int main() {
  std::string str = random_string(STR_LENGTH);
  std::string substr = "pizza";

  int idx = find_string(str, substr);
  std::cout << "Found " << substr << " at index " << idx << std::endl;

  return 0;
}
