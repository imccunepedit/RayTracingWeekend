// int* ptr -> stores memory adress of an int
// = &var -> gets the memor address of some variable
// *prt -> gets the values stored at the address specified by ptr
// int& ref = var -> reference to the variable, like passing address of variable and dereferencing
// cant change var later, always need int&

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
      // create colors for the current pixel, stored as double between 0 and 1
      double r = double(i) / (image_width-1);
      double g = double(j) / (image_height-1);
      double b = 0;

      // convert double (or maybe float eventually) to int between 0 and 255
      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);


      // write a line with the current pixel color
      std::cout << ir << " " << ig << " " << ib << "\n";

    }
  }

  // finish logging
  std::clog << "\rDone.";

  return 0;
}
