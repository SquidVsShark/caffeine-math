#ifndef VEC4_SSE_INLINE_INCLUDED_084B42B1_5ABC_4DFA_B980_7631EDA6EAEB
#define VEC4_SSE_INLINE_INCLUDED_084B42B1_5ABC_4DFA_B980_7631EDA6EAEB


#include "../detail/detail.hpp"
#include "vec_types.hpp"
#include "../general/general.hpp"
#include <assert.h>


#ifdef MATH_ON_SSE2

/*
  Vector4
  4D vector sse impl.
*/


namespace math {


// Constants
vec4
vec4_zero()
{
  const float zero = 0.f;
  return(_mm_load_ps1(&zero));
}


vec4
vec4_one()
{
  const float one = 1.f;
  return(_mm_load_ps1(&one));
}


vec4
vec4_zero_zero_zero_one()
{
  const float data[] = {0.f, 0.f, 0.f, 1.f};
  return(_mm_load_ps(data));
}


// Initialize

vec4
vec4_init(const float val)
{
  return(_mm_load_ps1(&val));
}


vec4
vec4_init(const float x, const float y, const float z, const float w)
{
  return(_mm_set_ps(w, z, y, x));
}


vec4
vec4_init_with_array(const float *arr)
{
  return(_mm_load_ps(arr));
}


// Get components.

float
vec4_get_x(const vec4 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[0];
}


float
vec4_get_y(const vec4 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[1];
}


float
vec4_get_z(const vec4 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[2];
}


float
vec4_get_w(const vec4 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[3];
}


void
vec4_to_array(const vec4 a, float *out_array)
{
  // TODO: Need to make sure out_array is 16 bytes aligned some how.
  _mm_store_ps(out_array, a);
}


vec4
vec4_add(const vec4 a, const vec4 b)
{
  return(_mm_add_ps(a, b));
}


vec4
vec4_subtract(const vec4 a, const vec4 b)
{
  return(_mm_sub_ps(a, b));
}


vec4
vec4_multiply(const vec4 a, const vec4 b)
{
  return(_mm_mul_ps(a, b));
}


vec4
vec4_divide(const vec4 a, const vec4 b)
{
  return(_mm_div_ps(a, b));
}


vec4
vec4_lerp(const vec4 start, const vec4 end, const float dt)
{
  const vec4 difference = vec4_subtract(end, start);
  const vec4 scaled     = vec4_scale(difference, dt);
  const vec4 position   = vec4_add(start, scaled);

  return position;
}


// vec4
// vec4_slerp(const vec4 start, const vec4 end, const float dt)
// {

// }



vec4
vec4_scale(const vec4 a, const float scale)
{
  const vec4 scale_vec = vec4_init(scale);
  return vec4_multiply(a, scale_vec);
}


vec4
vec4_normalize(const vec4 a)
{
  const float length = vec4_length(a);

  assert(length != 0); // Don't pass zero vectors. (0,0,0,0);

  return vec4_scale(a, (1.f / length));
}


float
vec4_length(const vec4 a)
{
  __m128 sq = _mm_mul_ps(a, a);

  sq = _mm_add_ps(sq, _mm_movehl_ps(sq, sq));
  sq = _mm_add_ss(sq, _mm_shuffle_ps(sq, sq, 1));
  sq = _mm_sqrt_ps(sq);

  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], sq);
  return vec_store[0];
}


float
vec4_dot(const vec4 a, const vec4 b)
{
  __m128 mu = _mm_mul_ps(a, b);

  mu = _mm_add_ps(mu, _mm_movehl_ps(mu, mu));
  mu = _mm_add_ss(mu, _mm_shuffle_ps(mu, mu, 1));

  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], mu);
  return vec_store[0];
}


bool
vec4_is_equal(const vec4 a, const vec4 b)
{
  return !!_mm_movemask_ps(_mm_cmpeq_ps(a, b));
}


bool
vec4_is_not_equal(const vec4 a, const vec4 b)
{
	return !vec4_is_equal(a, b);
}


bool
vec4_is_near(const vec4 a, const vec4 b, const float error)
{
  return(
    is_near(vec4_get_x(a), vec4_get_x(b), error)
    &&
    is_near(vec4_get_y(a), vec4_get_y(b), error)
    &&
    is_near(vec4_get_z(a), vec4_get_z(b), error)
    &&
    is_near(vec4_get_w(a), vec4_get_w(b), error)
  );
}


bool
vec4_is_not_near(const vec4 a, const vec4 b, const float error)
{
	return !vec4_is_near(a, b, error);
}


} // ns


#endif // use sse
#endif // inc guard
