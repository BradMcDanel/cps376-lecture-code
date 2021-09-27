#include <omp.h>
#include <iostream>

#include "image.h"

int main() {
  int scale = 4;
  Image img("../data/fm.png");
  Image out_img(img.w / scale, img.h / scale);

  // Goal: Use OpenMP to downsample the image by a factor of scale (4x).

  return 0;
}
