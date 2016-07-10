#ifndef VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C
#define VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C


#include "../detail/detail.hpp"


/*
  Vector Types.
  These are the vector types.
*/


#ifdef MATH_ON_SSE2
#define SIMD_TYPE __m128
#else
//typedef decltype(nullptr) nulltype;
#define SIMD_TYPE int
#endif


namespace math {

struct vec4
{
  union
  {
    SIMD_TYPE simd_vec;
    float data[4];
  };
};


struct vec3
{
  union
  {
    SIMD_TYPE simd_vec;
    float data[3];
  };
};


struct vec2
{
  union
  {
    SIMD_TYPE simd_vec;
    float data[2];
  };
};


} // ns


#endif // inc guard
