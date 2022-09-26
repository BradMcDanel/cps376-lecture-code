#ifndef _RANDOM_STRING_H_
#define _RANDOM_STRING_H_

#include <random>
#include <string>

std::string random_string(int length) {
  // Create a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 25);

  std::string str(length, 0);
  for (int i = 0; i < length; i++) {
    str[i] = 'a' + dis(gen);
  }
  return str;
}

#endif // _RANDOM_STRING_H_
