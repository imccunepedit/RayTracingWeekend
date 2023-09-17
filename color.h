#ifndef COLOR_H_
#define COLOR_H_

#include "vec3.h"

#include <iostream>


// makes code nicer to read and easier to understand
using color = vec3;


void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // divide the resulting color to finish averaging multiple samples
  auto scale = 1.0 /samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // translate the color to 0-255 and write it out seperatred by spaces
  static const interval intensity(0.000, 0.999);
  out << static_cast<int>(256 * intensity.clamp(r)) << " "
      << static_cast<int>(256 * intensity.clamp(g)) << " "
      << static_cast<int>(256 * intensity.clamp(b)) << "\n";
}


#endif // COLOR_H_
