#ifndef GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0
#define GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0


#include "../vec/vec3.hpp"


namespace math {


struct aabb
{
  math::vec3 max;
  math::vec3 min;
};


struct ray
{
  math::vec3 start;
  math::vec3 dir;
};


} // ns


#endif // inc guard
