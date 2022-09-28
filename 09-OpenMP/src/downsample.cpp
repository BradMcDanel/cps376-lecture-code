#include <iostream>
#include <omp.h>

#include "image.h"

int main() {
  int scale = 32;
  Image img("../data/fm.png");
  Image out_img(img.w / scale, img.h / scale);

  // downsamples the image by a factor of scale (32x here) using OpenMP
  // Example: this sets the 0,0 pixel of out_img to the 4,4 pixel of img
  out_img.set(0, 0, img.get(4, 4));
  out_img.write("../data/fm_out.png");

  return 0;
}
