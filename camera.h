#ifndef CAMERA_H_
#define CAMERA_H_

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "vec3.h"

class camera {
  public:
    double aspect_ratio      = 1.0; // ration of image width over height
    int    image_width       = 100; // rendered image width in pixel count
    int    samples_per_pixel = 10;  // number of random samples per pixel
    int    max_depth         = 10;  // max number of bounces into scene

    double vfov = 90;
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);

    double defocus_angle = 0;
    double focus_dist = 10;

    color background = color(0,0,0);

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
            pixel_color += ray_color(r, max_depth, world);
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
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    void initialize() {
      image_height = static_cast<int>(image_width/aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;

      center = lookfrom;

      // veiwport
      auto theta = degrees_to_radians(vfov);
      auto h = tan(theta/2);
      auto viewport_height = 2 * h * focus_dist;
      // set width based on the image since maybe the integer rounding casued them to skew from the aspect ratio
      auto viewport_width = viewport_height * (double(image_width)/image_height);

      // calculate camera local coords
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w,u);

      // vectors define the viewport edges, v needs to be negative because 3d coords define y increasing up but image has zero at top
      auto viewport_u = viewport_width * u;
      auto viewport_v = viewport_height * - v;

      // calculate the pixle sizes
      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v = viewport_v / image_height;

      // find the position of the top left pixel
      auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
      pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v)/2;

      // calc camera defocus disk vecs
      auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle/2));
      defocus_disk_u = u * defocus_radius;
      defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) {
      // find postion of pixel in 3D
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto pixel_sample = pixel_center + pixel_sample_square();

      // get direction of ray from camera to pixel
      auto ray_origin = (defocus_angle <=0) ? center:defocus_disk_sample();
      auto ray_direction = pixel_sample - ray_origin;
      auto ray_time = random_double();

      // construct a ray and get color of it
      return ray(ray_origin, ray_direction, ray_time);
    }

    vec3 pixel_sample_square() const {
      auto px = -0.5 + random_double();
      auto py = -0.5 + random_double();

      return (px*pixel_delta_u) + (py*pixel_delta_v);
    }

    point3 defocus_disk_sample() const {
      auto p = random_in_unit_disk();
      return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
      hit_record rec;

      if (depth <= 0) return color(0,0,0);


      if (!world.hit(r, interval(0.001, infinity), rec)) {
        return background;
      }
      ray scattered;
      color attenuation;
      color emission = rec.mat->emitted();

      if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return emission;

      color color_from_scatter =  attenuation * ray_color(scattered, depth - 1, world);
      return emission + color_from_scatter;

    }
};

#endif // CAMERA_H_
