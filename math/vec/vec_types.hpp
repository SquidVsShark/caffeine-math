#ifndef VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C
#define VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C


#include "../detail/detail.hpp"


/*
  Vector Types.
  These are the vector types in caffeine math.
*/


#ifdef MATH_ON_SSE2


namespace math {

using vec4 = __m128;
using vec3 = __m128;
using vec2 = __m128;

} // ns


#else // Fallback


namespace math {

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

} // ns


#endif // simd types


#endif // inc guard
