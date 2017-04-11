#ifndef GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0
#define GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0


#include "../detail/detail.hpp"
#include "../vec/vec3.hpp"


_MATH_NS_OPEN


struct ray
{
  MATH_NS_NAME::vec3 start;
  MATH_NS_NAME::vec3 end;
};


struct aabb
{
  MATH_NS_NAME::vec3 max;
  MATH_NS_NAME::vec3 min;
};


struct plane
{
  MATH_NS_NAME::vec3 position;
  MATH_NS_NAME::vec3 normal;
};


_MATH_NS_CLOSE


#endif // inc guard
