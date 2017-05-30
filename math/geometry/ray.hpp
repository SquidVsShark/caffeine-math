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
inline bool       ray_test_triangles(const ray &in_ray, const float tris[], const size_t tri_count, float *out_distance = nullptr);


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


bool
ray_test_triangles(
  const ray &in_ray,
  const float tris[],
  const size_t tri_count,
  float *out_distance)
{
  const vec3 r_dir = ray_direction(in_ray);
  
  for(size_t i = 0; i < tri_count; ++i)
  {
    const size_t tri = i * 3;
    const size_t tri_index = i * 3 * 3;
   
    const vec3 v0 = vec3_init_with_array(&tris[tri_index]);
    const vec3 v1 = vec3_subtract(vec3_init_with_array(&tris[tri_index + 3]), v0);
    const vec3 v2 = vec3_subtract(vec3_init_with_array(&tris[tri_index + 6]), v0);

    const vec3 p_vec = vec3_cross(r_dir, v2);
    const float dot  = vec3_dot(v1, p_vec);

    if(dot < MATH_NS_NAME::epsilon())
    {
      continue;
    }

    const float o_dot = 1 / dot;
    const vec3 t_vec  = vec3_subtract(in_ray.start, v0);
    const float u     = vec3_dot(t_vec, p_vec) * o_dot;
  
    if(!MATH_NS_NAME::is_between(u, 0.f, 1.f))
    {
      continue;
    }
 
    const vec3 q_vec = vec3_cross(t_vec, v1);
    const float v    = vec3_dot(r_dir, q_vec) * o_dot;
  
    if (v < 0 || u + v > 1)
    {
      continue;
    }
 
    const float t = vec3_dot(v2, q_vec) * o_dot;
  
    if(out_distance)
    {
      *out_distance = t;
    }
  
    return true;
    
  }
  
  return false;
}



_MATH_NS_CLOSE


#endif // inc guard
