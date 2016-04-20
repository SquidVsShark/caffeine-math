#ifndef VEC_FWD_INCLUDED_1E1D9FD5_8870_49DD_A293_93C1655C6E03
#define VEC_FWD_INCLUDED_1E1D9FD5_8870_49DD_A293_93C1655C6E03



#ifdef MATH_USE_SSE

#include <emmintrin.h> // SSE2

namespace math {

using vec4 = __m128;
using vec3 = __m128;
using vec2 = __m128;

} // ns

#else

namespace math {

class vec2;
class vec3;
class vec4;

} // ns

#endif


#endif // inc guard