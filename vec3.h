#ifndef VEC3_H_
#define VEC3_H_



#include "rtweekend.h"
#include <cmath>
#include <iostream>


using std::sqrt;

class vec3 {

  public:
    // array of 3 values, storing the elements of our vector
    double e[3];
    // constructor definitions for an empty vec3
    vec3() : e{0,0,0} {}
    // and a vec 3 with 3 values specified
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

    // expose the three elements of our vector as x, y, and z
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    // return a negative vec3
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    // return the value of the vec3 at the given index
    double operator[](int i) const { return e[i]; }
    // reference to the returned value this is just what the operator is expecting in some other cases
    double& operator[](int i) { return e[i]; }

    // add another vector onto this one
    vec3& operator+=(const vec3 &v) {
      e[0] += v.e[0];
      e[1] += v.e[1];
      e[2] += v.e[2];
      return *this;
    }
    // sclae this vector by some amount
    vec3& operator*=(const double t) {
      e[0] += t;
      e[1] += t;
      e[2] += t;
      return *this;
    }
    // we can use the *= operator to implement division
    vec3& operator/=(double t) {
      return *this *= 1/t;
    }

    // length uses sqrt which is taxing so we define length_squared elsewhere
    double length() const {
      return sqrt(length_squared());
    }
    double length_squared() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }


    bool near_zero() const {
      auto s = 1e-8;
      return (fabs(e[0]) < s) && (fabs(e[1]) < s ) && (fabs(e[2]) < s);
    }


    static vec3 random() {
      return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
      return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }
};


// point3 is just an alias for vec3 but just makes it more clear and easy to undersand later
using point3 = vec3;


// vecotr functions

// make << work nicely with vec3
// not sure what inline is exactly for, something maybe about it not being defined in the class
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}


// allow adding of two vectors
inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// allow subtraction fo two vectors
inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// implement elementwise multiplication of vectors, not sure why
inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// multiply a float by a vector
inline vec3 operator*(double t, const vec3 &v) {
  return vec3( t * v.e[0], t * v.e[1], t * v.e[2]);
}

// multiply vector by float
inline vec3 operator*(const vec3 &v, double t) {
  return t*v;
}

// dived vector by float
inline vec3 operator/(vec3 v, double t) {
  return (1/t) * v;
}


// dot product between 2 vecs
inline double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0]
       + u.e[1] * v.e[1]
       + u.e[2] * v.e[2];
}


// cross 2 vecs
inline vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// return a normalized vector
inline vec3 unit_vector(vec3 v) {
  return v/v.length();
}

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1,1);
    if (p.length_squared() < 1) return p;
  }
}

inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}


inline vec3 random_in_unit_disk() {
  while (true) {
    auto p = vec3(random_double(-1,1), random_double(-1,1), 0 );
    if (p.length_squared() < 1)
      return p;
  }
}


inline vec3 random_on_hemisphere(const vec3& normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0)
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}


vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n , double etai_over_etat) {
  auto cost_theta = fmin(dot(-uv, n), 1.0);
  vec3 r_out_perp = etai_over_etat * (uv + cost_theta*n);
  vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_parallel + r_out_perp;
}

#endif // VEC3_H_
