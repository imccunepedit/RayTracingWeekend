#ifndef COLOR_H_
#define COLOR_H_

#include "vec3.h"

#include <iostream>


// makes code nicer to read and easier to understand
using color = vec3;


void write_color(std::ostream &out, color pixel_color) {
  // translate the color to 0-255 and write it out seperatred by spaces
  out << static_cast<int>(255.999 * pixel_color.x()) << " "
      << static_cast<int>(255.999 * pixel_color.y()) << " "
      << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}


#endif // COLOR_H_
