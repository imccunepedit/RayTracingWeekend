// int* ptr -> stores memory adress of an int
// = &var -> gets the memor address of some variable
// *prt -> gets the values stored at the address specified by ptr
// int& ref = var -> reference to the variable, like passing address of variable and dereferencing
// cant change var later, always need int&

#include "rtweekend.h"

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "vec3.h"
#include <memory>




int main() {

  // hittable_list world;

  // auto material_ground = make_shared<lambertian>(color(0.5,0.5,0.5));
  // world.add(make_shared<sphere>(point3(0.0,-1000,0), 1000, material_ground));

  // for (int a = -11; a < 11; a++) {
  //   for (int b = -11; b < 11; b++) {
  //     auto choose_mat = random_double();
  //     point3 center(a+0.9*random_double(), 0.2, b+0.9*random_double());

  //     if ((center-point3(4,0.2,0)).length() > 0.9) {
  //       shared_ptr<material> sphere_material;

  //       if (choose_mat < 0.8) {
  //         //diffuse
  //         auto albedo = color::random() * color::random();
  //         sphere_material = make_shared<lambertian>(albedo);
  //         // auto center2 = center + vec3(0, random_double(0,0.5), 0);
  //         // world.add(make_shared<sphere>(center,center2,0.2, sphere_material));
  //         world.add(make_shared<sphere>(center,0.2, sphere_material));
  //       } else if (choose_mat < 0.95) {
  //         //metal
  //         auto albedo = color::random(0.5, 1);
  //         auto fuzz = random_double(0,0.5);
  //         sphere_material = make_shared<metal>(albedo,fuzz);
  //         world.add(make_shared<sphere>(center,0.2, sphere_material));
  //       } else {
  //         // glass
  //         sphere_material = make_shared<dielectric>(1.5);
  //         world.add(make_shared<sphere>(center, 0.2, sphere_material));
  //       }
  //     }
  //   }
  // }


  // auto material1 = make_shared<dielectric>(1.5);
  // world.add(make_shared<sphere>(point3(0,1,0), 1, material1));
  // auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
  // world.add(make_shared<sphere>(point3(-4,1,0), 1, material2));
  // auto material3 = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
  // world.add(make_shared<sphere>(point3(4,1,0), 1, material3));


  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(0.5,0.5,0.5));
  world.add(make_shared<sphere>(point3(0.0,-1000,0), 1000, material_ground));

  // auto material0 = make_shared<light>(color(2,1,.75));
  // world.add(make_shared<sphere>(point3(0,1,0), 0.7, material0));
  // auto material1 = make_shared<dielectric>(1.5);
  // world.add(make_shared<sphere>(point3(0,1,0), 1, material1));
  // auto material11 = make_shared<dielectric>(1.0/1.5);
  // world.add(make_shared<sphere>(point3(0,1,0), 0.8, material11));
  auto material2 = make_shared<lambertian>(color(1,1,1));
  world.add(make_shared<sphere>(point3(-4,1,0), 1, material2));
  // auto material3 = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
  // world.add(make_shared<sphere>(point3(4,1,0), 1, material3));


  world = hittable_list(make_shared<bvh_node>(world));

  camera cam;

  cam.aspect_ratio = 4.0 / 3.0;
  cam.image_width = 800;
  cam.samples_per_pixel = 1;
  cam.max_depth = 1;

  cam.vfov = 20;
  cam.lookfrom = point3(13,2,3);
  cam.lookat = point3(0,0,0);
  cam.vup = point3(0,1,0);

  cam.defocus_angle = 0;
  cam.focus_dist = 10.0;

  cam.background = color(0.95, 0.16, 0.1);

  cam.render(world);

  return 0;

}
