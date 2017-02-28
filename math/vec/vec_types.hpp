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
// in FPU mode SIMD_TYPE is nothing.
typedef decltype(nullptr) nulltype_t;
#define SIMD_TYPE nulltype_t
#endif


_MATH_NS_OPEN


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


_MATH_NS_CLOSE


#endif // inc guard
