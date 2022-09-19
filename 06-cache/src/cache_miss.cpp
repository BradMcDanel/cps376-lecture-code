#include <iostream>
#include <vector>
#include <algorithm>

#include "timer.h"

int main() {
  int linear_sum = 0, random_sum = 0;
  Timer t;
  std::vector<int> v(1024 * 1024);
  for (size_t i = 0; i < v.size(); i++) {
    v[i] = rand() % 100;
  }

  // Sum the vector with linear access pattern
  t.start();
  for (size_t i = 0; i < v.size(); i++) {
    linear_sum += v[i];
  }
  t.stop();
  std::cout << "Linear Access Time: " << t.elapsed() << " us" << std::endl;

  // Compute random permutation of vector indices
  std::vector<size_t> indices(v.size());
  for (size_t i = 0; i < indices.size(); i++) {
    indices[i] = i;
  }
  std::random_shuffle(indices.begin(), indices.end());

  // Sum the vector with random access pattern
  t.start();
  for (size_t i = 0; i < indices.size(); i++) {
    random_sum += v[indices[i]];
  }
  t.stop();
  std::cout << "Random Access Time: " << t.elapsed() << " us" << std::endl;

  if (linear_sum != random_sum) {
    std::cout << "Sums are equal? no" << std::endl;
  } else {
    std::cout << "Sums are equal? yes" << std::endl;
  }

  return 0;
}
