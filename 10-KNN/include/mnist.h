#ifndef _MNIST_H
#define _MNIST_H

#include <string>

#define MNIST_MEAN 0.13066047740239506
#define MNIST_STD 0.3081078038564623

struct Sample {
  float data[784];
  int label;
};

struct Dataset {
  Sample *samples;
  int size;
  ~Dataset() { delete[] samples; }
};

Dataset load_mnist(const std::string &img_path, const std::string &label_path);
Dataset load_mnist_train(const std::string &path);
Dataset load_mnist_test(const std::string &path);

void value_print(const Sample &sample);
void ascii_print(const Sample &sample);

#endif /* _MNIST_H */
