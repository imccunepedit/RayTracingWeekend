// int* ptr -> stores memory adress of an int
// = &var -> gets the memor address of some variable
// *prt -> gets the values stored at the address specified by ptr
// int& ref = var -> reference to the variable, like passing address of variable and dereferencing
// cant change var later, always need int&

#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"




int main() {

  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(1.4,1.3,1.4));
  auto material_center = make_shared<lambertian>(color(0.0,0.2,0.8));
  auto material_left = make_shared<metal>(color(0.8,0.8,0.8), 0.3);
  auto material_right = make_shared<metal>(color(0.8,0.2,0.6), 1.0);


  world.add(make_shared<sphere>(point3(0.0,-100.5,-1.4), 100.0, material_ground));
  world.add(make_shared<sphere>(point3(0.0,0.0,-1.4), 0.3, material_center));
  world.add(make_shared<sphere>(point3(-1.0,0.0,-1.4), 0.5, material_left));
  world.add(make_shared<sphere>(point3(1.0,0.0,-1.4), 0.5, material_right));


  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);

  return 0;

}
