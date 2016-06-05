#ifndef RAY_INCLUDED_9580B5C2_5FD1_4185_9537_C6C4F7EC3A4E
#define RAY_INCLUDED_9580B5C2_5FD1_4185_9537_C6C4F7EC3A4E


#include "geometry_types.hpp"


namespace math {


// ** Interface ** //

inline ray        ray_init(const vec3 start, const vec3 end);
inline vec3       ray_inverse(const ray &inverse);
inline float      ray_length(const ray &ray);


// ** Impl ** //


ray
ray_init(const vec3 start, const vec3 end)
{
  return ray{start, end};
}


vec3
ray_inverse(const ray &ray)
{
  // Get direction
  const vec3 dir = vec3_subtract(ray.end, ray.start);
  const vec3 inv = vec3_divide(vec3_one(), dir);

  return inv;
}


float
ray_length(const ray &ray)
{
  return vec3_lenth(vec3_subtract(ray.end, ray.start));
}


} // ns


#endif // inc guard
