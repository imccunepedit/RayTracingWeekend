#ifndef COLOR_H_
#define COLOR_H_

#include "vec3.h"

#include <iostream>


// makes code nicer to read and easier to understand
using color = vec3;

inline double linear_to_gamma(double linear_component) {
  return sqrt(linear_component);
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // divide the resulting color to finish averaging multiple samples
  auto scale = 1.0 /samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // gamma correct color
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);


  static const interval intensity(0.000, 0.999);

  int r_i = static_cast<int>(256 * intensity.clamp(r));
  int g_i = static_cast<int>(256 * intensity.clamp(g));
  int b_i = static_cast<int>(256 * intensity.clamp(b));

  // translate the color to 0-255 and write it out seperatred by spaces
  // out << r_i << " " << g_i << " " << b_i << "\n";
  out << r_i << g_i << b_i << 255;

  // out << std::hex << (((r_i & 0xff) << 24) + ((g_i & 0xff) << 16) + ((b_i & 0xff) << 8)  + (0xff));
}


#endif // COLOR_H_
