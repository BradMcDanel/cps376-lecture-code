#include <iostream>
#include <list>
#include <vector>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <size>" << std::endl;
    return 1;
  }

  std::vector<int> v1;
  int N = atoi(argv[1]);
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    v1.push_back(rand() % 100);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Vector (no pre-alloc): " << micros(end - start).count()
            << " us\n";

  std::vector<int> v2;
  v2.reserve(N); // pre-alloc N elements!
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N; ++i) {
    v2.push_back(rand() % 100);
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Vector (pre-alloc): " << micros(end - start).count() << " us\n";

  // compute v1 and v2 sums to prevent compiler from optimizing away
  // (this part isn't important for the benchmark)
  int sum1 = 0;
  for (int i : v1) {
    sum1 += i;
  }
  int sum2 = 0;
  for (int i : v2) {
    sum2 += i;
  }

  return 0;
}