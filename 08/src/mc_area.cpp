#include <omp.h>
#include <iostream>

#include "image.h"

int main() {
  // Reads in a image (and converts to greyscale for simplicity)
  Image img("../data/fm.png");

  // Get width and height of image
  std::cout << img.w << ", " << img.h << std::endl;

  // Get a pixel using .get
  std::cout << img.get(0, 0) << std::endl;

  // Save image to file
  img.write("../data/fm_out.png");

  // Goal: Use OpenMP to estimate area of non-zero pixels in the image
  //       We assume that a brute-force approach is too slow, so we use
  //       a Monte Carlo approach, with each thread sampling random
  //       points in the image.

  return 0;
}
