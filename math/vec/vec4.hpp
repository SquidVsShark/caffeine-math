#ifndef VEC4_INCLUDED_9C1AD544_35E1_456B_B882_DB0C9DAEBF09
#define VEC4_INCLUDED_9C1AD544_35E1_456B_B882_DB0C9DAEBF09


/*
  Vector4
  4D vector interface.
*/


#include "vec_types.hpp"
#include "../detail/detail.hpp"


namespace math {


// ** Interface ** //


// Constants
MATH_VEC4_INLINE vec4                   vec4_zero();
MATH_VEC4_INLINE vec4                   vec4_one();
MATH_VEC4_INLINE vec4                   vec4_zero_zero_zero_one();

// Initialize vector.
MATH_VEC4_INLINE vec4                   vec4_init(const float val);
MATH_VEC4_INLINE vec4                   vec4_init(const float x, const float y, const float z, const float w);
MATH_VEC4_INLINE vec4                   vec4_init_with_array(const float *arr);

// Get components.
MATH_VEC4_INLINE float                  vec4_get_x(const vec4 vec);
MATH_VEC4_INLINE float                  vec4_get_y(const vec4 vec);
MATH_VEC4_INLINE float                  vec4_get_z(const vec4 vec);
MATH_VEC4_INLINE float                  vec4_get_w(const vec4 vec);
MATH_VEC4_INLINE void                   vec4_to_array(const vec4 a, float *out_array);

// Component wise arithmetic.
MATH_VEC4_INLINE vec4                   vec4_add(const vec4 a, const vec4 b);
MATH_VEC4_INLINE vec4                   vec4_subtract(const vec4 a, const vec4 b);
MATH_VEC4_INLINE vec4                   vec4_multiply(const vec4 a, const vec4 b);
MATH_VEC4_INLINE vec4                   vec4_divide(const vec4 a, const vec4 b);

// Special operations.
MATH_VEC4_INLINE vec4                   vec4_lerp(const vec4 start, const vec4 end, const float dt);
//MATH_VEC4_INLINE vec4                 vec4_slerp(const vec4 start, const vec4 end, const float dt); // not impl
MATH_VEC4_INLINE vec4                   vec4_scale(const vec4 a, const float scale);
MATH_VEC4_INLINE vec4                   vec4_normalize(const vec4 a);
MATH_VEC4_INLINE float                  vec4_length(const vec4 a);
MATH_VEC4_INLINE float                  vec4_dot(const vec4 a, const vec4 b);

// Equality
MATH_VEC4_INLINE bool                   vec4_is_equal(const vec4 a, const vec4 b);
MATH_VEC4_INLINE bool                   vec4_is_not_equal(const vec4 a, const vec4 b);
MATH_VEC4_INLINE bool                   vec4_is_near(const vec4 a, const vec4 b, const float error);
MATH_VEC4_INLINE bool                   vec4_is_not_near(const vec4 a, const vec4 b, const float error);


} // ns


/*
  Include the correct impl
*/


#ifdef MATH_ON_SSE2

#include "vec4_sse.inl"

#else

#include "vec4_fallback.inl"

#endif // impl choice


#endif // inc guard
