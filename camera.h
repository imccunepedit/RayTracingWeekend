#ifndef CAMERA_H_
#define CAMERA_H_

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"

class camera {
public:
  double aspect_ratio      = 1.0;
  int    image_width       = 100;
  int    samples_per_pixel = 10;


  void render(const hittable& world) {
    initialize();

    // P3 means asci color
    // then set image width and height and max color
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";


    // loop over each pixel to create a uv coords texture
    for (int j = 0; j < image_height; j++) {
      // print to standard log how many lines of the image still need to be renderd
      std::clog << "\rScanlines remaining: " << (image_height -j) << " " << std::flush;
      for (int i = 0; i < image_width; i++) {
        color pixel_color(0,0,0);
        for (int sample = 0; sample < samples_per_pixel; ++sample) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world);
        }
        write_color(std::cout, pixel_color, samples_per_pixel);
      }
    }

    // finish logging
    std::clog << "\rDone.              ";



  }

private:
  int image_height;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;



  void initialize() {
    image_height = static_cast<int>(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = point3(0,0,0);


    // veiwport
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    // set width based on the image since maybe the integer rounding casued them to skew from the aspect ratio
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);


    // vectors define the viewport edges, v needs to be negative because 3d coords define y increasing up but image has zero at top
    auto viewport_u = vec3(viewport_width, 0 ,0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // calculate the pixle sizes
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // find the position of the top left pixel
    auto viewport_upper_left = center
      - vec3(0,0,focal_length) - (viewport_u + viewport_v)/2;
    pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v)/2;
  }

  ray get_ray(int i, int j) {
    // find postion of pixel in 3D
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    // get direction of ray from camera to pixel
    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    // construct a ray and get color of it
    return ray(ray_origin, ray_direction);
  }

  vec3 pixel_sample_square() const {
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();

    return (px*pixel_delta_u) + (py*pixel_delta_v);
  }




  color ray_color(const ray& r, const hittable& world) const {
    hit_record rec;

    if (world.hit(r, interval(0, infinity), rec)) {
      return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    // the y coord of our direction goes from -1 to 1 but lerp needs from 0 to 1
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
  }
};

#endif // CAMERA_H_
