#ifndef TRANSFORM_TYPES_INCLUDED_8D47B2F6_5764_483F_98BA_CE06AEEFB50C
#define TRANSFORM_TYPES_INCLUDED_8D47B2F6_5764_483F_98BA_CE06AEEFB50C


#include "../detail/detail.hpp"
#include "../quat/quat.hpp"
#include "../vec/vec3.hpp"


_MATH_NS_OPEN


struct transform
{
  vec3     position;
  vec3     scale; 
  quat     rotation;
}; // class


_MATH_NS_CLOSE


#endif // include guard
