#include <iostream>
#include <omp.h>
#include <vector>

#include "mnist.h"

// Copy over code from the serial implementation
int main() {
  Dataset train = load_mnist_train("../data/mnist_images");
  Dataset test = load_mnist_test("../data/mnist_images");

  return 0;
}
