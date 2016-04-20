#ifndef DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42
#define DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42


#include <emmintrin.h>


#ifdef MATH_ENABLE_SIMD
#define MATH_NO_SIMD
#define MATH_SSE2
#endif


#ifdef MATH_FORCE_INLINE
#define MATH_INLINE __forceinline
#else
#define MATH_INLINE inline
#endif


#define MATH_CONST __attribute__((const))

#define MATH_LIKELY(x)       __builtin_expect((x),1)
#define MATH_UNLIKELY(x)     __builtin_expect((x),0)


#define MATH_VEC2_INLINE MATH_INLINE
#define MATH_VEC3_INLINE MATH_INLINE
#define MATH_VEC4_INLINE MATH_INLINE
#define MATH_MAT3_INLINE MATH_INLINE
#define MATH_MAT4_INLINE MATH_INLINE
#define MATH_QUAT_INLINE MATH_INLINE
#define MATH_GENR_INLINE MATH_INLINE
#define MATH_CONSTEXPR constexpr


#endif // include guard
