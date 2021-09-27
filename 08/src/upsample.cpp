#include <omp.h>
#include <iostream>

#include "image.h"

int main() {
  int scale = 4;
  Image img("../data/fm.png");
  Image out_img(img.w * scale, img.h * scale);

  // Goal: Use OpenMP to upsample the image by a factor of sacle (4x).

  return 0;
}
