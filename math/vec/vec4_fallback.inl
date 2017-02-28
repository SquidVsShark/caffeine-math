#ifndef VEC4_FALLBACK_INLINE_INCLUDED_443986F2_8DC2_4E3F_AB4A_CF1C6B0894AF
#define VEC4_FALLBACK_INLINE_INCLUDED_443986F2_8DC2_4E3F_AB4A_CF1C6B0894AF


#include "../detail/detail.hpp"
#include "vec_types.hpp"
#include "../general/general.hpp"
#include <assert.h>


#ifdef MATH_ON_FPU


/*
  Vector4
  4D vector fallback impl.
*/


_MATH_NS_OPEN


// ** Implimentation ** //


// Constants
vec4
vec4_zero()
{
  return vec4_init(0.f);
}


vec4
vec4_one()
{
  return vec4_init(1.f);
}


vec4
vec4_zero_zero_zero_one()
{
  return vec4_init(0.f, 0.f, 0.f, 1.f);
}


// Initialize

vec4
vec4_init(const float val)
{
  return vec4_init(val, val, val, val);
}


vec4
vec4_init(const float x, const float y, const float z, const float w)
{
  vec4 return_vec;

  return_vec.data[0] = x;
  return_vec.data[1] = y;
  return_vec.data[2] = z;
  return_vec.data[3] = w;

  return return_vec;
}


vec4
vec4_init_with_array(const float *arr)
{
  return vec4_init(arr[0], arr[1], arr[2], arr[3]);
}


// Get components.

float
vec4_get_x(const vec4 vec)
{
  return vec.data[0];
}


float
vec4_get_y(const vec4 vec)
{
  return vec.data[1];
}


float
vec4_get_z(const vec4 vec)
{
  return vec.data[2];
}


float
vec4_get_w(const vec4 vec)
{
  return vec.data[3];
}


void
vec4_to_array(const vec4 a, float *out_array)
{
  out_array[0] = vec4_get_x(a);
  out_array[1] = vec4_get_y(a);
  out_array[2] = vec4_get_z(a);
  out_array[3] = vec4_get_w(a);
}


vec4
vec4_add(const vec4 a, const vec4 b)
{
  return vec4_init(get_x(a) + get_x(b), get_y(a) + get_y(b), get_z(a) + get_z(b), get_w(a) + get_w(b));
}


vec4
vec4_subtract(const vec4 a, const vec4 b)
{
  return vec4_init(get_x(a) - get_x(b), get_y(a) - get_y(b), get_z(a) - get_z(b), get_w(a) - get_w(b));
}


vec4
vec4_multiply(const vec4 a, const vec4 b)
{
  return vec4_init(get_x(a) * get_x(b), get_y(a) * get_y(b), get_z(a) * get_z(b), get_w(a) * get_w(b));
}


vec4
vec4_divide(const vec4 a, const vec4 b)
{
  // Divide by zero check.
  assert(get_x(b) != 0 && get_y(b) != 0 && get_z(b) != 0 && get_w(b) != 0);

  return vec4_init(get_x(a) / get_x(b), get_y(a) / get_y(b), get_z(a) / get_z(b), get_w(a) / get_w(b));
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
  const float x = get_x(a) * get_x(a) + get_y(a) * get_y(a) + get_z(a) * get_z(a) + get_w(a) * get_w(a);

  return sqrt(x);
}


float
vec4_dot(const vec4 a, const vec4 b)
{
   return (vec4_get_x(a) * vec4_get_x(b)) +
          (vec4_get_y(a) * vec4_get_y(b)) +
          (vec4_get_z(a) * vec4_get_z(b)) +
          (vec4_get_w(a) * vec4_get_w(b));
}


bool
vec4_is_equal(const vec4 a, const vec4 b)
{
	return
  (
    (vec4_get_x(a) == vec4_get_x(b))
    &&
    (vec4_get_y(a) == vec4_get_y(b))
    &&
    (vec4_get_z(a) == vec4_get_z(b))
    &&
    (vec4_get_w(a) == vec4_get_w(b))
  );
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


_MATH_NS_CLOSE


#endif // on fpu
#endif // inc guard
