// int* ptr -> stores memory adress of an int
// = &var -> gets the memor address of some variable
// *prt -> gets the values stored at the address specified by ptr
// int& ref = var -> reference to the variable, like passing address of variable and dereferencing
// cant change var later, always need int&

#include "color.h"
#include "vec3.h"

#include <iostream>



int main() {

  // image

  int image_width = 256;
  int image_height = 256;


  // render

  // P3 means asci color
  // then set image width and height and max color
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";


  // loop over each pixel to create a uv coords texture
  for (int j = 0; j < image_height; j++) {
    // print to standard log how many lines of the image still need to be renderd
    std::clog << "\rScanlines remaining: " << (image_height -j) << " " << std::flush;
    for (int i = 0; i < image_width; i++) {
      color pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
      write_color(std::cout, pixel_color);
    }
  }

  // finish logging
  std::clog << "\rDone.";

  return 0;
}
