#include <iostream>
#include <omp.h>
#include <vector>

int main() {
  std::vector<float> data = {1, 2, 3, 4, 5, 6, 7, 8};
  float sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < data.size(); i++) {
    sum += data[i];
  }
  std::cout << sum << std::endl;
  return 0;
}
