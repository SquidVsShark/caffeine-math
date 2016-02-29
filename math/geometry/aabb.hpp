#ifndef AABB_INCLUDED_0C5E26F6_BFB1_422A_948B_0E4861927EEE
#define AABB_INCLUDED_0C5E26F6_BFB1_422A_948B_0E4861927EEE


#include "geometry_types.hpp"
#include "../vec/vec3.hpp"
#include "../general/general.hpp"
#include <stddef.h>
#include <assert.h>


namespace math {


// ** Interface ** //

inline aabb         aabb_from_xyz_array(const float vertex[], const size_t number_of_floats);
inline bool         aabb_intersection_test(const aabb &a, const aabb &b);
inline bool         aabb_intersection_ray_test(const ray &ray, const aabb &box);


// ** Impl ** //


aabb
aabb_from_xyz_array(const float vertex[],
                    const size_t number_of_floats)
{
  aabb out_aabb;

  // Check is valid.
  assert((number_of_floats % 3) == 0);
  if((number_of_floats % 3) != 0)
  {
    return out_aabb;
  }

  // Calculate min, max
  float max_x(vertex[0]);
  float max_y(vertex[1]);
  float max_z(vertex[2]);

  float min_x(vertex[0]);
  float min_y(vertex[1]);
  float min_z(vertex[2]);

  for(size_t i = 0; i < number_of_floats / 3; ++i)
  {
    size_t index = i * 3;

    max_x = max(vertex[index + 0], max_x);
    min_x = min(vertex[index + 0], min_x);

    max_y = max(vertex[index + 1], max_y);
    min_y = min(vertex[index + 1], min_y);

    max_z = max(vertex[index + 2], max_z);
    min_z = min(vertex[index + 2], min_z);
  }

  out_aabb.max = vec3_init(max_x, max_y, max_z);
  out_aabb.min = vec3_init(min_x, min_y, min_z);

  // Calculate extents
  out_aabb.extents = vec3_scale(vec3_subtract(out_aabb.max, out_aabb.min), 0.5f);

  // Calculate origin.
  const float origin_x = vec3_get_x(out_aabb.max) - (vec3_get_x(out_aabb.half_extents));
  const float origin_y = vec3_get_y(out_aabb.max) - (vec3_get_y(out_aabb.half_extents));
  const float origin_z = vec3_get_z(out_aabb.max) - (vec3_get_z(out_aabb.half_extents));

  out_aabb.origin = vec3_init(origin_x, origin_y, origin_z);

  return out_aabb;
}


namespace detail
{
  // Simple Single Axis Therom test.
  // We assume we are dealing with just AABB boxes.
  inline bool
  sat_test(const float origin_a,
           const float origin_b,
           const float combined_length)
  {
    return math::abs(origin_b - origin_a) < combined_length;
  }
} // ns


bool
aabb_intersection_test(const aabb &a,
                       const aabb &b)
{
  return (sat_test(math::vec3_get_x(a.origin), math::vec3_get_x(b.origin), (math::vec3_get_x(a.half_extent) + math::vec3_get_x(b.half_extent))) &&
          sat_test(math::vec3_get_y(a.origin), math::vec3_get_y(b.origin), (math::vec3_get_y(a.half_extent) + math::vec3_get_y(b.half_extent))) &&
          sat_test(math::vec3_get_z(a.origin), math::vec3_get_z(b.origin), (math::vec3_get_z(a.half_extent) + math::vec3_get_z(b.half_extent)));
}



bool
aabb_intersection_ray_test(const ray &ray, conset aabb &box)
{
  return false;
}



} // ns


#endif // inc guard
