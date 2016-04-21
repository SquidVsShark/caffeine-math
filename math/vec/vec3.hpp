#ifndef VEC3_INCLUDED_DD26787F_2663_4F50_85D0_7188D23BA64B
#define VEC3_INCLUDED_DD26787F_2663_4F50_85D0_7188D23BA64B


/*
  Vector3
  3D vector interface.
*/


#include "../detail/detail.hpp"
#include "vec_types.hpp"


namespace math {


// ** Interface ** //

// Constants
MATH_VEC3_INLINE vec3                   vec3_zero();
MATH_VEC3_INLINE vec3                   vec3_one();
MATH_VEC3_INLINE vec3                   vec3_zero_zero_one();

// Initialize vector.
MATH_VEC3_INLINE vec3                   vec3_init(const float val);
MATH_VEC3_INLINE vec3                   vec3_init(const float x, const float y, const float z);
MATH_VEC3_INLINE vec3                   vec3_init_with_array(const float *arr);

// Get components.
MATH_VEC3_INLINE float                  vec3_get_x(const vec3 vec);
MATH_VEC3_INLINE float                  vec3_get_y(const vec3 vec);
MATH_VEC3_INLINE float                  vec3_get_z(const vec3 vec);
MATH_VEC3_INLINE void                   vec3_to_array(const vec3 a, float *out_array);

// Component wise arithmetic.
MATH_VEC3_INLINE vec3                   vec3_add(const vec3 a, const vec3 b);
MATH_VEC3_INLINE vec3                   vec3_subtract(const vec3 a, const vec3 b);
MATH_VEC3_INLINE vec3                   vec3_multiply(const vec3 a, const vec3 b);
MATH_VEC3_INLINE vec3                   vec3_divide(const vec3 a, const vec3 b);

// Special operations.
MATH_VEC3_INLINE vec3                   vec3_lerp(const vec3 start, const vec3 end, const float dt);
//MATH_VEC3_INLINE vec3                vec3_slerp(const vec3 start, const vec3 end, const float dt);
MATH_VEC3_INLINE vec3                   vec3_scale(const vec3 a, const float scale);
MATH_VEC3_INLINE vec3                   vec3_normalize(const vec3 a);
MATH_VEC3_INLINE float                  vec3_length(const vec3 a);
MATH_VEC3_INLINE vec3                   vec3_cross(const vec3 a, const vec3 b);
MATH_VEC3_INLINE float                  vec3_dot(const vec3 a, const vec3 b);

// ** Equal Test ** //
MATH_VEC3_INLINE bool                   vec3_is_equal(const vec3 a, const vec3 b);
MATH_VEC3_INLINE bool                   vec3_is_not_equal(const vec3 a, const vec3 b);
MATH_VEC3_INLINE bool                   vec3_is_near(const vec3 a, const vec3 b, const float error);
MATH_VEC3_INLINE bool                   vec3_is_not_near(const vec3 a, const vec3 b, const float error);


} // ns


// What impl to use

#ifdef MATH_ON_SSE2

#include "vec3_sse.inl"

#else

#include "vec3_fallback.inl"

#endif // Choose which impl to use.s

#endif // inc guard
