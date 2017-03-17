#ifndef GEOMETRY_INCLUDED_98853631_728E_4E3F_AC27_065504B13942
#define GEOMETRY_INCLUDED_98853631_728E_4E3F_AC27_065504B13942


#include "../detail/detail.hpp"
#include "geometry_types.hpp"
#include "../vec/vec3.hpp"
#include "aabb.hpp"


_MATH_NS_OPEN


// ----------------------------------------------------------- [ Interface ] --


MATH_GENR_INLINE aabb            aabb_init();


// ---------------------------------------------------------------- [ Impl ] --


aabb
aabb_init()
{
  return { math::vec3_zero(), math::vec3_zero() };
}


_MATH_NS_CLOSE


#endif // inc guard
