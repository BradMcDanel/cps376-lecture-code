#include <iostream>
#include <list>
#include <vector>

#include "timer.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <size>" << std::endl;
    return 1;
  }

  Timer t;
  int N = atoi(argv[1]);
  std::vector<int> v1, v2;
  v2.reserve(N); // pre-alloc N elements!

  t.start();
  for (int i = 0; i < N; ++i) {
    v1.push_back(i);
  }
  t.stop();
  std::cout << "Vector (no pre-alloc): " << t.elapsed() << " us\n";

  t.start();
  for (int i = 0; i < N; ++i) {
    v2.push_back(i);
  }
  t.stop();
  std::cout << "Vector (pre-alloc): " << t.elapsed() << " us\n";

  // compute v1 and v2 sums to prevent compiler from optimizing away
  // (this part isn't important for the benchmark)
  // Don't worry about the overflow
  int sum1 = 0;
  for (int i : v1) {
    sum1 += i;
  }
  int sum2 = 0;
  for (int i : v2) {
    sum2 += i;
  }

  if (sum1 != sum2) {
    std::cout << "Sums are equal? no" << std::endl;
  } else {
    std::cout << "Sums are equal? yes" << std::endl;
  }

  return 0;
}