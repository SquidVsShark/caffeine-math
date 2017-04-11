#ifndef RAY_INCLUDED_9580B5C2_5FD1_4185_9537_C6C4F7EC3A4E
#define RAY_INCLUDED_9580B5C2_5FD1_4185_9537_C6C4F7EC3A4E


#include "../detail/detail.hpp"
#include "geometry_types.hpp"


_MATH_NS_OPEN


// ----------------------------------------------------------- [ Interface ] --


inline ray        ray_init(const vec3 start, const vec3 end);
inline ray        ray_inverse(const ray &inverse);
inline float      ray_length(const ray &ray);
inline vec3       ray_direction(const ray &ray);

inline float      ray_test_aabb(const ray &ray, const aabb &target);
inline bool       ray_test_plane(const ray &ray, const plane &target, float *out_distance = nullptr);


// ---------------------------------------------------------------- [ Impl ] --


ray
ray_init(const vec3 start, const vec3 end)
{
  return ray{start, end};
}


ray
ray_inverse(const ray &ray)
{
  return ray_init(ray.end, ray.start);
}


float
ray_length(const ray &ray)
{
  return vec3_length(vec3_subtract(ray.end, ray.start));
}


vec3
ray_direction(const ray &ray)
{
  return vec3_normalize(vec3_subtract(ray.end, ray.start));
}


float
ray_test_aabb(const ray &in_ray, const aabb &box)
{
  const vec3 ray_dir = ray_direction(in_ray);
  constexpr float no_hit = 0.f;

  float t[10];
  
  t[1] = (get_x(box.min) - get_x(in_ray.start)) / get_x(ray_dir);
  t[2] = (get_x(box.max) - get_x(in_ray.start)) / get_x(ray_dir);
  t[3] = (get_y(box.min) - get_y(in_ray.start)) / get_y(ray_dir);
  t[4] = (get_y(box.max) - get_y(in_ray.start)) / get_y(ray_dir);
  t[5] = (get_z(box.min) - get_z(in_ray.start)) / get_z(ray_dir);
  t[6] = (get_z(box.max) - get_z(in_ray.start)) / get_z(ray_dir);
  
  t[7] = MATH_NS_NAME::max(
           MATH_NS_NAME::max(
             MATH_NS_NAME::min(t[1], t[2]),
             MATH_NS_NAME::min(t[3], t[4])
           ),
           MATH_NS_NAME::min(t[5], t[6])
         );
  
  
  t[8] = MATH_NS_NAME::min(
           MATH_NS_NAME::min(
             MATH_NS_NAME::max(t[1], t[2]),
             MATH_NS_NAME::max(t[3], t[4])
           ),
           MATH_NS_NAME::max(t[5], t[6])
         );
  
  t[9] = (t[8] < 0 || t[7] > t[8]) ? no_hit : t[7];
  
  return t[9];
}


bool
ray_test_plane(const ray &in_ray, const plane &target, float *out_distance)
{
  const vec3 ray_dir = ray_direction(in_ray);

  const float dot = vec3_dot(target.normal, ray_dir);
  
  if (MATH_NS_NAME::abs(dot) > MATH_NS_NAME::epsilon())
  {
    const vec3 distance = vec3_subtract(target.position, in_ray.start);
    const float dot_norm = vec3_dot(distance, target.normal) / dot;
    
    if(out_distance)
    {
      *out_distance = dot_norm;
    }
    
    if(dot_norm >= 0)
    {
      return true;
    }
  }
  
  return false;
}


_MATH_NS_CLOSE


#endif // inc guard
