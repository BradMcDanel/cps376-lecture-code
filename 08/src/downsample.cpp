#include <omp.h>
#include <iostream>

#include "image.h"

int main() {
  int scale = 32;
  Image img("../data/fm.png");
  Image out_img(img.w / scale, img.h / scale);

// downsamples the image by a factor of scale (32x here) using OpenMP
#pragma omp parallel for collapse(2)
  for (int i = 0; i < out_img.h; i++) {
    for (int j = 0; j < out_img.w; j++) {
      out_img.set(i, j, img.get(i * scale, j * scale));
    }
  }

  out_img.write("../data/fm_out.png");

  return 0;
}
