#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "rtweekend.h"

#include "hittable_list.h"
#include "vec3.h"
#include <memory>

class hit_record;
using color = vec3;

class material {
  public:
    virtual ~material() = default;

    virtual color emitted() const {
      return color(0,0,0);
    }

    virtual bool scatter (
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {return 0;}
};




class lambertian : public material {
  public:
    lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
      auto scatter_direction = rec.normal + random_unit_vector();

      if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

      scattered = ray(rec.p, scatter_direction, r_in.time());
      attenuation = albedo;
      return true;
    }

  private:
    color albedo;
};



class metal : public material {
  public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
      vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
      reflected = reflected + fuzz*random_unit_vector();
      scattered = ray(rec.p, reflected, r_in.time());
      attenuation = albedo;
      return (dot(scattered.direction(), rec.normal) > 0);
    }
  private:
    color albedo;
    double fuzz;
};


class dielectric : public material {
  public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
      attenuation = color(1.0,1.0,1.0);
      double ri = rec.front_face ? (1/refraction_index) : refraction_index;

      vec3 unit_direction = unit_vector(r_in.direction());
      double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
      double sin_theta = sqrt(1.0-cos_theta*cos_theta);

      bool cannot_refract = ri * sin_theta > 1.0;
      vec3 direction;

      if (cannot_refract || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, rec.normal);
      else
        direction = refract(unit_direction, rec.normal, ri);

      scattered = ray(rec.p, direction, r_in.time());
      return true;
    }


  private:
    double refraction_index;

    static double reflectance(double cosine, double refraction_index) {
      auto r0 = (1-refraction_index) / (1+refraction_index);
      r0 = r0*r0;
      return r0 + (1-r0)*pow((1-cosine),5);
    }
};

class light : public material {
  public:
    light(const color& a) : emission(a) {}

    color emitted() const override {
      return emission;
    }

  private:
    color emission;
};


#endif // MATERIAL_H_
