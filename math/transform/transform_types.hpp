#ifndef TRANSFORM_TYPES_INCLUDED_8D47B2F6_5764_483F_98BA_CE06AEEFB50C
#define TRANSFORM_TYPES_INCLUDED_8D47B2F6_5764_483F_98BA_CE06AEEFB50C


#include "../quat/quat.hpp"
#include "../vec/vec3.hpp"


namespace math {


struct transform
{
  transform() {}

  quat     rotation  = quat_init(0.f,0.f,0.f,1.f);
  vec3     scale     = vec3_init(1.f,1.f,1.f);
  vec3     position  = vec3_init(0.f,0.f,0.f);
}; // class


} // namespace


#endif // include guard