#include <iostream>
#include <list>
#include <vector>

#include "timer.h"

int main() {
  int list_sum = 0, vector_sum = 0;
  std::vector<int> v(1024 * 1024);
  std::list<int> l(1024 * 1024);
  Timer t;

  for (int i = 0; i < 1024 * 1024; ++i) {
    int value = rand() % 100;
    v[i] = value;
    l.push_back(value);
  }

  t.start();
  for (auto i : v) {
    vector_sum += i;
  }
  t.stop();
  std::cout << "Vector Time: " << t.elapsed() << "us\n";

  t.start();
  for (auto i : l) {
    list_sum += i;
  }
  t.stop();
  std::cout << "List Time: " << t.elapsed() << "us\n";

  // check that the sums are the same
  if (vector_sum != list_sum) {
    std::cout << "Sums are equal? no" << std::endl;
  } else {
    std::cout << "Sums are equal? yes" << std::endl;
  }

  return 0;
}
