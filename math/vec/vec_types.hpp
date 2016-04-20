#ifndef VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C
#define VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C


/*
  Vector Types.
  These are the vector types in caffeine math.
*/


#include "../detail/detail.hpp"

#define MATH_USE_SSE


namespace math {


// To access the components you should go through the vector interface.


#ifdef MATH_USE_SSE

using vec4 = __m128;
using vec3 = __m128;
using vec2 = __m64;

#else

class vec4
{
  float data[4];
};

class vec3
{
  float data[3];
};

class vec2
{
  float data[2];
};

#endif

  
} // namespace


#endif // include guard