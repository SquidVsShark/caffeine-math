#ifndef GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E
#define GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E


/*
  These are general math functions and constants.
  Alot of them are simple stub functions to allow
  for easy overriding if required.
*/


#include "../detail/detail.hpp"
#include <math.h>
#include <cmath>
#include <algorithm>
#include <random>


namespace math {


// ** INTERFACE ** //


// ** Constants ** //

MATH_CONSTEXPR float                pi()          { return 3.14159265359f;  }
MATH_CONSTEXPR float                two_pi()      { return 2.f * pi();      }
MATH_CONSTEXPR float                half_pi()     { return pi() * 0.5f;     }
MATH_CONSTEXPR float                tau()         { return two_pi();        }
MATH_CONSTEXPR float                half_tau()    { return pi();            }
MATH_CONSTEXPR float                quart_tau()   { return half_pi();       }
MATH_CONSTEXPR float                g_ratio()     { return 1.61803398875f;  }
MATH_CONSTEXPR float                root_two()    { return 1.41421356237f;  }
MATH_CONSTEXPR float                root_three()  { return 1.73205080757f;  }
MATH_CONSTEXPR float                epsilon()     { return 0.000000001f;    }


// ** Trig ** //

MATH_GENR_INLINE float              tan(const float x);
MATH_GENR_INLINE float              a_tan2(const float x, const float y);
MATH_GENR_INLINE float              cos(const float radians);
MATH_GENR_INLINE float              a_cos(const float radians);
MATH_GENR_INLINE float              sin(const float radians);
MATH_GENR_INLINE float              a_sin(const float radians);


// ** Degs/Rads ** //

MATH_GENR_INLINE float              radians_to_degrees(const float radians);
MATH_GENR_INLINE float              degrees_to_radians(const float degrees);


// ** Casting ** //

MATH_GENR_INLINE float              to_float(const uint32_t x);
MATH_GENR_INLINE float              to_float(const int32_t x);
MATH_GENR_INLINE int32_t            to_int(const float x);
MATH_GENR_INLINE uint32_t           to_uint(const float x);


// ** Random ** //

MATH_GENR_INLINE float              rand_range(const float start, const float end);
MATH_GENR_INLINE uint32_t           rand_range(const uint32_t start, const uint32_t end);
MATH_GENR_INLINE int32_t            rand_range(const int32_t start, const int32_t end);


// ** Other general ** //

MATH_GENR_INLINE float              sqrt(const float x);
MATH_GENR_INLINE float              abs(const float x);
MATH_GENR_INLINE int32_t            abs(const int32_t x);

MATH_GENR_INLINE float              max(const float a, const float b);
MATH_GENR_INLINE int32_t            max(const int32_t a, const int32_t b);
MATH_GENR_INLINE uint32_t           max(const uint32_t a, const uint32_t b);

MATH_GENR_INLINE float              min(const float a, const float b);
MATH_GENR_INLINE int32_t            min(const int32_t a, const int32_t b);
MATH_GENR_INLINE uint32_t           min(const uint32_t a, const uint32_t b);

MATH_GENR_INLINE float              max_length(const float a, const float b);
MATH_GENR_INLINE float              min_length(const float a, const float b);

MATH_GENR_INLINE float              clamp(const float x, const float between_a, const float between_b);
MATH_GENR_INLINE bool               is_between(const float to_check, const float a, const float b);
MATH_GENR_INLINE bool               is_near(const float a, const float b, const float error_margin);

MATH_GENR_INLINE bool               is_pow_two(const uint32_t i);
  
MATH_GENR_INLINE float              sign(const float x); // Returns 1 or -1
MATH_GENR_INLINE float              mod(const float x, const float divisor);
MATH_GENR_INLINE uint32_t           mod(const int32_t value, const uint32_t divisor);

MATH_GENR_INLINE float              ceil(const float x);
MATH_GENR_INLINE float              floor(const float x);
MATH_GENR_INLINE float              nearest_floor(const float x, const float increments);


// ** IMPL ** //


float
max_length(const float a, const float b)
{
  if(math::abs(a) >= math::abs(b))
  {
    return a;
  }
  
  return b;
}


float
min_length(const float a, const float b)
{
  if(math::abs(a) <= math::abs(b))
  {
    return a;
  }
  
  return b;
}


float
sqrt(const float x)
{
  return sqrtf(x);
}


float
max(const float x, const float y)
{
  return fmaxf(x, y);
}


int32_t
max(const int32_t x, const int32_t y)
{
  return std::max(x, y);
}


uint32_t
max(const uint32_t x, const uint32_t y)
{
  return std::max(x, y);
}


float
min(const float x, const float y)
{
  return fminf(x, y);
}


int32_t
min(const int32_t x, const int32_t y)
{
  return std::min(x, y);
}



uint32_t
min(const uint32_t x, const uint32_t y)
{
  return std::min(x, y);
}


float
clamp(const float x, const float between_a, const float between_b)
{
  const float highest = between_a >= between_b ? between_a : between_b;
  const float lowest  = between_a != highest ? between_a : between_b;

  if(x >= highest)
  {
    return highest;
  }
  else if(x <= lowest)
  {
    return lowest;
  }

  return x;
}


bool
is_between(const float value, const float limit_a, const float limit_b)
{
  const float min = math::min(limit_a, limit_b);
  const float max = math::max(limit_a, limit_b);
  
  return value > min && value < max;
}


float
abs(const float x)
{
  return fabsf(x);
}


int32_t
abs(const int32_t x)
{
  return std::abs(x);
}


float
tan(const float x)
{
  return tanf(x);
}


float
a_tan2(const float x, const float y)
{
  return atan2f(x, y);
}


float
cos(const float radians)
{
  return cosf(radians);
}


float
a_cos(const float radians)
{
  return acosf(radians);
}


float
sin(const float radians)
{
  return sinf(radians);
}


float
a_sin(const float radians)
{
  return asinf(radians);
}


namespace detail
{
  MATH_CONSTEXPR float over_pi()  { return 180.f / pi(); }
  MATH_CONSTEXPR float over_180() { return pi() / 180.f; }
}


float
radians_to_degrees(const float radians)
{
  return radians * detail::over_pi();
}


float
degrees_to_radians(const float degrees)
{
  return degrees * detail::over_180();
}


float
sign(const float x)
{
  return x >= 0.f ? 1.f : -1.f;
}


bool
is_pow_two(const uint32_t i)
{
  return (i & (i - 1)) == 0;
}


float
ceil(const float x)
{
  return ((float)(long)((x)+1));
}


float
floor(const float x)
{
  return ((float)(long)x);
}


bool
is_near(const float a, const float b, const float error_margin)
{
  const float abs_error = abs(error_margin);

  return abs(b - a) <= abs_error;
}


float
mod(const float x, const float divisor)
{
  float mod = fmodf(x, divisor);
  
  if(mod < 0)
  {
    mod += divisor;
  }
  
  return mod;
}


uint32_t
mod(const int32_t value, const uint32_t divisor)
{
  int32_t mod = value % (int32_t)divisor;
  
  if(mod < 0)
  {
    mod += divisor;
  }
  
  return mod;
}


float
nearest_floor(const float x, const float increments)
{
  const float s = sign(x);
  
  const float remainder = mod(abs(x), increments);
  return (abs(x) - remainder) * s;
}


float
to_float(const uint32_t x)
{
  return (float)x;
}


float
to_float(const int32_t x)
{
  return (float)x;
}


int32_t
to_int(const float x)
{
  return (int32_t)x;
}


uint32_t
to_uint(const float x)
{
  return (uint32_t)x;
}


float
rand_range(const float start, const float end)
{
  static std::random_device rd;
  static std::default_random_engine re(rd());
  
  std::uniform_real_distribution<float> dist(start, end);

  return dist(re);
}


uint32_t
rand_range(const uint32_t start, const uint32_t end)
{
  static std::random_device rd;
  static std::default_random_engine re(rd());
  
  std::uniform_int_distribution<uint32_t> dist(start, end);

  return dist(re);
}


int32_t
rand_range(const int32_t start, const int32_t end)
{
  static std::random_device rd;
  static std::default_random_engine re(rd());
  
  std::uniform_int_distribution<int32_t> dist(start, end);

  return dist(re);
}


} // namespace


#endif // include guard
