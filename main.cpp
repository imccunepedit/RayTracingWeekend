// int* ptr -> stores memory adress of an int
// = &var -> gets the memor address of some variable
// *prt -> gets the values stored at the address specified by ptr
// int& ref = var -> reference to the variable, like passing address of variable and dereferencing
// cant change var later, always need int&

#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>


double hit_sphere(const point3& center, double radius, const ray& r) {
  // see section 5.1 for explanation of math -> https://raytracing.github.io/books/RayTracingInOneWeekend.html
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius*radius;
  auto discriminant = half_b*half_b - a*c;


  // simplifying the vector expression for a sphere with some origin we can check wether a point is inside it or not based on the discriminant of this simplified function
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - sqrt(discriminant)) / a;
  }



}


color ray_color(const ray& r) {
  // get the hit position of our sphere, retunrs -1 if no hit
  auto t = hit_sphere(point3(0,0,-1), 0.5, r);

  // if theres a hit get the normal vector at the point of intersection
  if (t > 0.0) {
    vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
    return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
  }

  vec3 unit_direction = unit_vector(r.direction());
  // the y coord of our direction goes from -1 to 1 but lerp needs from 0 to 1
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

  // Image

  auto aspect_ratio = 16.0/9.0;
  int image_width = 400;

  // calculate the image height based on the widht and aspect ratio
  int image_height = static_cast<int>(image_width/aspect_ratio);

  // Camera
  auto focal_length = 1.0;
  auto camera_center = point3(0,0,0);

  // set width and height based on the image since maybe the integer rounding casued them to skew from the aspect ratio
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

  // vectors define the viewport edges, v needs to be negative because 3d coords define y increasing up but image has zero at top
  auto viewport_u = vec3(viewport_width, 0 ,0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // calculate the pixle sizes
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // find the position of the top left pixel
  auto viewport_upper_left = camera_center
                           - vec3(0,0,focal_length) - (viewport_u + viewport_v)/2;
  auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v)/2;


  // Render

  // P3 means asci color
  // then set image width and height and max color
  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";


  // loop over each pixel to create a uv coords texture
  for (int j = 0; j < image_height; j++) {
    // print to standard log how many lines of the image still need to be renderd
    std::clog << "\rScanlines remaining: " << (image_height -j) << " " << std::flush;
    for (int i = 0; i < image_width; i++) {

      // find postion of pixel in 3D
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

      // get direction of ray from camera to pixel
      auto ray_direction = pixel_center - camera_center;

      // construct a ray and get color of it
      ray r(camera_center, ray_direction);
      color pixel_color = ray_color(r);

      // write color to screen
      write_color(std::cout, pixel_color);
    }
  }

  // finish logging
  std::clog << "\rDone.              ";

  return 0;
}
