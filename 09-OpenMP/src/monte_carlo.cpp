#include <iostream>
#include <omp.h>
#include <vector>

int main() {
  int num_samples = 1000000;
  int num_inside = 0;
  // generate random points between 0 and 1
  // check if they are inside the circle
  // if x^2 + y^2 < 1, then the point is inside the circle
  //   - if so, increment num_inside
  //   - if not, do nothing
  // estimate pi = 4 * num_inside / num_samples

  // After you have the correct answer, try using OpenMP to parallelize it!
}
