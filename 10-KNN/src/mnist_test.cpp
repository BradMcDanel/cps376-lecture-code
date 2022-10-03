#include <iostream>

#include "mnist.h"

int main() {
  // Dataset *train = load_mnist_train("../data/mnist_images");
  Dataset test = load_mnist_test("../data/mnist_images");
  // std::cout << train.size << std::endl;
  std::cout << test.size << std::endl;

  for (int i = 0; i < 3; i++) {
    std::cout << test.samples[i].label << std::endl;
    ascii_print(test.samples[i]);
  }
  return 0;
}
