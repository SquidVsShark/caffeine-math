#ifndef GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0
#define GEOMETRY_TYPES_INCLUDED_5C543B7A_4C9E_45FE_91BD_F072716934F0


#include "../vec/vec3.hpp"


namespace math {


struct aabb
{
  math::vec3 max;
  math::vec3 min;
  math::vec3 half_extents;
  math::vec3 origin;
};


struct ray
{
  math::vec3 start;
  math::vec3 end;
};


} // ns


#endif // inc guard
