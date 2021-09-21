#include <iostream>
#include <list>
#include <vector>

// Just to make it easier to read...
template <typename T> std::chrono::microseconds micros(T duration) {
  return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

int main() {
  std::vector<int> v(1024 * 1024);
  std::list<int> l(1024 * 1024);

  for (int i = 0; i < 1024 * 1024; ++i) {
    int value = rand() % 100;
    v[i] = value;
    l.push_back(value);
  }

  // Compare the runtime for iterating over both containers
  auto start = std::chrono::high_resolution_clock::now();
  int sum = 0;
  for (auto i : v) {
    sum += i;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Vector Time: " << micros(end - start).count() << "us\n";

  start = std::chrono::high_resolution_clock::now();
  sum = 0;
  for (auto i : l) {
    sum += i;
  }
  end = std::chrono::high_resolution_clock::now();
  std::cout << "Sum: " << sum << std::endl;
  std::cout << "List Time: " << micros(end - start).count() << "us\n";

  return 0;
}