#ifndef SPHERE_H_
#define SPHERE_H_

#include "rtweekend.h"
#include "hittable.h"


class sphere : public hittable {
  public:
    sphere(point3 _center, double _radius, shared_ptr<material> _material)
      : center(_center), radius(_radius), mat(_material) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
      // a b and c for quadratic formula
      vec3 oc = r.origin() - center;
      auto a = r.direction().length_squared();
      auto half_b = dot(oc, r.direction());
      auto c = oc.length_squared() - radius*radius;

      auto discriminant = half_b*half_b - a*c;

      // if there are no real solutions for the sqrt no need to compute, just return no hit
      if (discriminant < 0) return false;
      auto sqrtd = sqrt(discriminant);

      auto root = (-half_b - sqrtd)/a;
      if (!ray_t.surrounds(root)) {
        root = (-half_b + sqrtd)/a;
        if (!ray_t.surrounds(root))
          return false;
      }


      rec.t = root;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - center) / radius;
      rec.set_face_normal(r, outward_normal);
      rec.mat = mat;

      return true;
    }


  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif // SPHERE_H_
