#ifndef RTWEEKEND_H_
#define RTWEEKEND_H_

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utiliy functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  // rand number from 0 up to but not including 1
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  return min + (max-min) * random_double();
}

inline int random_int(int min, int max) {
  return int(random_double(min, max+1));
}


// Common Headers


#include "interval.h"
#include "vec3.h"
#include "ray.h"

#endif // RTWEEKEND_H_
