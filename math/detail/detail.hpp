#ifndef DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42
#define DETAIL_INCLUDED_738ADE13_1093_4593_AF81_2F9CB58DAE42

// Intrinsics settings

#ifdef MATH_USE_SIMD
#define MATH_ON_SSE2
#include <emmintrin.h>
#else
#define MATH_ON_FPU
#endif


// Windows Inline
#ifdef _WIN32

#define MATH_INLINE inline __force_inline

// GCC and Clang support this method.
#elif defined __has_attribute

  // Will likely always exist, but in case it doesn't.
  #if __has_attribute(always_inline)
  #define MATH_INLINE inline __attribute__((always_inline))
  // Fallback to regular inline.
  #else
  #define MATH_INLINE inline
  #endif

// Fallback to regular inline.
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
