#ifndef VECTOR2_INCLUDED_077ABD34_E392_49BA_8472_D6541EF2744E
#define VECTOR2_INCLUDED_077ABD34_E392_49BA_8472_D6541EF2744E


/*
  Vector2
  2D vector interface.
*/


#include "../detail/detail.hpp"
#include "vec_types.hpp"


namespace math {


// ** Interface ** //

// ** Constants ** //
MATH_VEC2_INLINE vec2                   vec2_zero();
MATH_VEC2_INLINE vec2                   vec2_one();
MATH_VEC2_INLINE vec2                   vec2_zero_one();

// ** Initialize new vectors ** //
MATH_VEC2_INLINE vec2                   vec2_init(const float val);
MATH_VEC2_INLINE vec2                   vec2_init(const float x, const float y);
MATH_VEC2_INLINE vec2                   vec2_init_with_array(const float *arr);

// ** Get elements ** //
MATH_VEC2_INLINE float                  vec2_get_x(const vec2 vec);
MATH_VEC2_INLINE float                  vec2_get_y(const vec2 vec);
MATH_VEC2_INLINE void                   vec2_to_array(const vec2 a, float *out_array);

// ** Arithmetic ** //
MATH_VEC2_INLINE vec2                   vec2_add(const vec2 a, const vec2 b);
MATH_VEC2_INLINE vec2                   vec2_subtract(const vec2 a, const vec2 b);
MATH_VEC2_INLINE vec2                   vec2_multiply(const vec2 a, const vec2 b);
MATH_VEC2_INLINE vec2                   vec2_divide(const vec2 a, const vec2 b);

// ** Special Operations ** //
MATH_VEC2_INLINE vec2                   vec2_lerp(const vec2 start, const vec2 end, const float dt);
//MATH_VEC2_INLINE vec2                 vec2_slerp(); // not impl
MATH_VEC2_INLINE vec2                   vec2_scale(const vec2 a, const float scale);
MATH_VEC2_INLINE vec2                   vec2_normalize(const vec2 a);
MATH_VEC2_INLINE float                  vec2_length(const vec2 a);
MATH_VEC2_INLINE float                  vec2_cross(const vec2 a, const vec2 b);
MATH_VEC2_INLINE float                  vec2_dot(const vec2 a, const vec2 b);

// ** Equal Test ** //
MATH_VEC2_INLINE bool                   vec2_is_equal(const vec2 a, const vec2 b);
MATH_VEC2_INLINE bool                   vec2_is_not_equal(const vec2 a, const vec2 b);
MATH_VEC2_INLINE bool                   vec2_is_near(const vec2 a, const vec2 b, const float error);
MATH_VEC2_INLINE bool                   vec2_is_not_near(const vec2 a, const vec2 b, const float error);


} // ns


// What impl to use?

#ifdef MATH_ON_SSE2

#include "vec2_sse.inl"

#else

#include "vec2_fallback.inl"

#endif // Choose which impl to use.

#endif // inc guard
