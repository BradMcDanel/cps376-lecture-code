#include <iostream>
#include <omp.h>

// showcase critical section for reduction
int main() {
  int sum = 0;
  int data[8] = {1, 2, 3, 4, 5, 6, 7, 8};

#pragma omp parallel for
  for (int i = 0; i < 8; i++) {
    // run this program a few times and see what happens. why?
    // (uncomment this line and try again!)
    //  #pragma omp critical
    sum += data[i];
  }
  std::cout << "Expected: 36, Actual: " << sum << std::endl;
}
