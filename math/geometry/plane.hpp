#ifndef PLANE_INCLUDED_45A3D802_C8E0_4369_B9CA_3AC4810E8DDD
#define PLANE_INCLUDED_45A3D802_C8E0_4369_B9CA_3AC4810E8DDD


#include "../detail/detail.hpp"
#include "geometry_types.hpp"


_MATH_NS_OPEN


// ----------------------------------------------------------- [ Interface ] --


inline plane        plane_init(const vec3 position, const vec3 normal);


// ---------------------------------------------------------------- [ Impl ] --


inline plane
plane_init(const vec3 position, const vec3 normal)
{
  return plane{ position, normal };
}



_MATH_NS_CLOSE


#endif // inc guard
