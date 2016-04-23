#ifndef VEC3_SSE_INCLUDED_7FCC7E5E_C1B2_4281_B76B_9B1065958FC6
#define VEC3_SSE_INCLUDED_7FCC7E5E_C1B2_4281_B76B_9B1065958FC6


#include "../detail/detail.hpp"
#include "vec_types.hpp"
#include "../general/general.hpp"
#include <assert.h>


#ifdef MATH_ON_SSE2


/*
  Vector3
  3D vector sse impl.
*/


namespace math {


// Constants
vec3
vec3_zero()
{
  const float zero = 0.f;
  return(_mm_load_ps1(&zero));
}


vec3
vec3_one()
{
  const float one = 1.f;
  return(_mm_load_ps1(&one));
}


vec3
vec3_zero_zero_one()
{
  const float data[] = {0.f, 0.f, 1.f, 0.f};
  return(_mm_load_ps(data));
}


vec3
vec3_init(const float val)
{
  return(_mm_load_ps1(&val));
}


vec3
vec3_init(const float x, const float y, const float z)
{
  const float zero = 0;
  return(_mm_set_ps(zero, z, y, x));
}


vec3
vec3_init_with_array(const float *arr)
{
  return(_mm_load_ps(arr));
}


// Get components.

float
vec3_get_x(const vec3 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[0];
}


float
vec3_get_y(const vec3 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[1];
}


float
vec3_get_z(const vec3 vec)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], vec);
  return vec_store[2];
}


void
vec3_to_array(const vec3 a, float *out_array)
{
  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], a);

  memcpy(out_array, &vec_store[0], sizeof(float) * 3);
}


vec3
vec3_add(const vec3 a, const vec3 b)
{
  return(_mm_add_ps(a, b));
}


vec3
vec3_subtract(const vec3 a, const vec3 b)
{
  return(_mm_sub_ps(a, b));
}


vec3
vec3_multiply(const vec3 a, const vec3 b)
{
  return(_mm_mul_ps(a, b));
}


vec3
vec3_divide(const vec3 a, const vec3 b)
{
  return(_mm_div_ps(a, b));
}


vec3
vec3_lerp(const vec3 start, const vec3 end, const float dt)
{
  const vec3 difference = vec3_subtract(end, start);
  const vec3 scaled     = vec3_scale(difference, dt);
  const vec3 position   = vec3_add(start, scaled);

  return position;
}


// vec3
// vec3_slerp(const vec3 start, const vec3 end, const float dt)
// {
//   const float dot                   = vec3_dot(start, end);
//   const float clamp                 = caffmath::clamp(dot, -1.f, 1.f);
//   const float theta                 = caffmath::a_cos(clamp) * dt;

//   const vec3 start_scale         = vec3_scale(start, dot);
//   const vec3 relative            = vec3_subtract(end, start_scale);
//   const vec3 normal              = vec3_normalize(relative);

//   const float cos_theta             = caffmath::cos(theta);
//   const float sin_theta             = caffmath::sin(theta);

//   const vec3 start_cos_scale     = vec3_scale(start, cos_theta);
//   const vec3 relative_sin_scale  = vec3_scale(normal, sin_theta);

//   return vec3_add(start_cos_scale, relative_sin_scale);
// }


vec3
vec3_scale(const vec3 a, const float scale)
{
  const vec3 scale_vec = vec3_init(scale);
  return vec3_multiply(a, scale_vec);
}


vec3
vec3_normalize(const vec3 a)
{
  const float length = vec3_length(a);

  assert(length != 0); // Don't pass zero vectors. (0,0,0);

  return vec3_scale(a, (1.f / length));
}


float
vec3_length(const vec3 a)
{
  __m128 sq = _mm_mul_ps(a, a);

  sq = _mm_add_ps(sq, _mm_movehl_ps(sq, sq));
  sq = _mm_add_ss(sq, _mm_shuffle_ps(sq, sq, 1));
  sq = _mm_sqrt_ps(sq);

  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], sq);
  return vec_store[0];
}


vec3
vec3_cross(const vec3 a, const vec3 b)
{
  // TODO: Better way with sse?

  const float x = (vec3_get_y(a) * vec3_get_z(b)) - (vec3_get_z(a) * vec3_get_y(b));
  const float y = (vec3_get_x(a) * vec3_get_z(b)) - (vec3_get_z(a) * vec3_get_x(b));
  const float z = (vec3_get_x(a) * vec3_get_y(b)) - (vec3_get_y(a) * vec3_get_x(b));

  return vec3_init(x, -y, z);
}


float
vec3_dot(const vec3 a, const vec3 b)
{
  __m128 mu = _mm_mul_ps(a, b);

  mu = _mm_add_ps(mu, _mm_movehl_ps(mu, mu));
  mu = _mm_add_ss(mu, _mm_shuffle_ps(mu, mu, 1));


  __declspec(align(16)) float vec_store[4];
  _mm_store_ps(&vec_store[0], mu);
  return vec_store[0];
}


bool
vec3_is_equal(const vec3 a, const vec3 b)
{
  return !!_mm_movemask_ps(_mm_cmpeq_ps(a, b));
}


bool
vec3_is_not_equal(const vec3 a, const vec3 b)
{
	return !vec3_is_equal(a, b);
}


bool
vec3_is_near(const vec3 a, const vec3 b, const float error)
{
  return(
    is_near(vec3_get_x(a), vec3_get_x(b), error)
    &&
    is_near(vec3_get_y(a), vec3_get_y(b), error)
    &&
    is_near(vec3_get_z(a), vec3_get_z(b), error)
  );
}


bool
vec3_is_not_near(const vec3 a, const vec3 b, const float error)
{
	return !vec3_is_near(a, b, error);
}


} // ns


#endif // use sse
#endif // inc guard
