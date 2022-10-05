#include <fstream>
#include <iostream>
#include <string>

#include "image.h"
#include "mnist.h"

Dataset load_mnist(const std::string &img_path, const std::string &label_path,
                   int size) {
  Dataset dataset;
  dataset.size = size;
  dataset.samples = new Sample[dataset.size];

  std::ifstream labels(label_path);

  for (int i = 0; i < dataset.size; i++) {
    labels >> dataset.samples[i].label;
  }

  labels.close();

  for (int i = 0; i < dataset.size; i++) {
    // fancy percentage display (overwrite each time)
    std::cout << "\r Loading " << img_path << ": "
              << (i + 1) * 100 / dataset.size << "%";
    std::cout.flush();

    std::string full_image_path = img_path + "/" + std::to_string(i) + ".png";
    Image image(full_image_path.c_str());
    char *data = (char *)image.data;
    for (int j = 0; j < 784; j++) {
      float val = (float)data[j] / 255.0;
      val = std::abs(val);
      dataset.samples[i].data[j] = val;
    }
  }

  return dataset;
}

Dataset load_mnist_train(const std::string &path) {
  std::string train_dir = path + "/train";
  std::string train_labels = path + "/train_labels.txt";

  return load_mnist(train_dir, train_labels, 60000);
}

Dataset load_mnist_test(const std::string &path) {
  std::string test_dir = path + "/test";
  std::string test_labels = path + "/test_labels.txt";

  return load_mnist(test_dir, test_labels, 10000);
}

void value_print(const Sample &sample) {
  std::cout << std::fixed;
  std::cout.precision(3);

  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      std::cout << sample.data[i * 28 + j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout.unsetf(std::ios::fixed);
  std::cout << std::endl;
}

void ascii_print(const Sample &sample) {
  std::string shades = " .:-=+*#%@";

  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      float value = sample.data[i * 28 + j];
      int index = value * (shades.size() - 1);
      if (index < 0)
        index = 0;
      if (index >= (int)shades.size())
        index = shades.size() - 1;
      std::cout << shades[index];
    }
    std::cout << std::endl;
  }
}
