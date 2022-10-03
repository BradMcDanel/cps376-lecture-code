#include <iostream>
#include <omp.h>
#include <vector>

#include "mnist.h"

#define NUM_PIXELS 784

float distance(const Sample &a, const Sample &b) {
  // TODO: Compute l2 distance between a and b
  // Use NUM_PIXELS to get the number of pixels in a sample
  // All samples have the same number of pixels
}

int knn(const Sample &sample, const Dataset &dataset, int k) {
  // TODO: Find the k nearest neighbors of sample in dataset
  // This function should return the label of the majority
  // of the k nearest neighbors. If there is a tie, return
  // just pick one of the labels with the majority.

  // 1. Use the distance function to compute the distance
  //    between sample and each sample in dataset
  // 2. Sort the distances in ascending order
  // 3. Find the k nearest neighbors
  // 4. Find the majority label
}

int main(int argc, char *argv[]) {
  Dataset train = load_mnist_train("../data/mnist_images");
  Dataset test = load_mnist_test("../data/mnist_images");

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <k>" << std::endl;
    return 1;
  }

  // K is the number of nearest neighbors to consider
  int k = atoi(argv[1]);

  // TODO:
  // 1. Implement distance function
  // 2. Implement k-nearest neighbor algorithm
  // 3. Compute accuracy (and print it)
  // 4. Compare performance with different k

  return 0;
}
