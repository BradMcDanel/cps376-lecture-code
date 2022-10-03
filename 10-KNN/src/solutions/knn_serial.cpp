#include <algorithm>
#include <iostream>
#include <omp.h>
#include <vector>

#include "mnist.h"

#define NUM_PIXELS 784
#define NUM_CLASSES 10

std::vector<int> argsort(std::vector<float> &v) {
  std::vector<int> idx(v.size());
  for (size_t i = 0; i < idx.size(); i++) {
    idx[i] = i;
  }
  std::sort(idx.begin(), idx.end(),
            [&v](int i1, int i2) { return v[i1] < v[i2]; });

  return idx;
}

float distance(const Sample &a, const Sample &b) {
  float dist = 0;
  for (int i = 0; i < NUM_PIXELS; i++) {
    float diff = a.data[i] - b.data[i];
    dist += diff * diff;
  }
  return dist;
}

int knn(const Sample &sample, const Dataset &dataset, int k) {
  std::vector<int> class_counts(NUM_CLASSES);
  std::vector<int> neighbors(k);
  std::vector<float> dists(dataset.size);
  for (int i = 0; i < dataset.size; i++) {
    dists[i] = distance(sample, dataset.samples[i]);
  }

  std::vector<int> idx = argsort(dists);

  for (int i = 0; i < k; i++) {
    neighbors[i] = dataset.samples[idx[i]].label;
  }

  for (int i = 0; i < k; i++) {
    class_counts[neighbors[i]]++;
  }

  int max_count = 0;
  int max_idx = 0;
  for (int i = 0; i < NUM_CLASSES; i++) {
    if (class_counts[i] > max_count) {
      max_count = class_counts[i];
      max_idx = i;
    }
  }

  return max_idx;
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

  // perform knn for each sample in the test set
  int correct = 0;
  for (int i = 0; i < test.size; i++) {
    int pred = knn(test.samples[i], train, k);
    if (pred == test.samples[i].label) {
      correct++;
    }
    std::cout << "Current accuracy: " << (float)correct / (i + 1) << std::endl;
  }

  std::cout << "Accuracy: " << (float)correct / test.size << std::endl;

  return 0;
}
