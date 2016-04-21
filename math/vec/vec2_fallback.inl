#ifndef VECTOR2_FALLBACK_INCLUDED_E819F68F_EE77_4C08_8B2D_152123C0C47A
#define VECTOR2_FALLBACK_INCLUDED_E819F68F_EE77_4C08_8B2D_152123C0C47A


#include "../detail/detail.hpp"
#include "vec_types.hpp"
#include "../general/general.hpp"
#include <assert.h>


#ifdef MATH_ON_FPU


/*
  Vector2
  2D vector fallback impl.
*/

namespace math {


// This is not part of public interface, keep walking :)
// Using anything in the detail namespace is undefined-behaviour.
namespace detail
{
  struct internal_vec2
  {
    float x, y;
  };
}


// Constants

vec2
vec2_zero()
{
  return vec2_init(0.f);
}


vec2
vec2_one()
{
  return vec2_init(1.f);
}


vec2
vec2_zero_one()
{
  return vec2_init(0.f, 1.f);
}

// Initialize

vec2
vec2_init(const float val)
{
  return vec2_init(val, val);
}


vec2
vec2_init(const float x, const float y)
{
  vec2 return_vec;
  detail::internal_vec2 *internal_vec = reinterpret_cast<detail::internal_vec2*>(&return_vec);

  internal_vec->x = x;
  internal_vec->y = y;

  return return_vec;
}


vec2
vec2_init_with_array(const float *arr)
{
  return vec2_init(arr[0], arr[1]);
}


// Get components.

float
vec2_get_x(const vec2 vec)
{
  const detail::internal_vec2 *internal_vec = reinterpret_cast<const detail::internal_vec2*>(&vec);
  return internal_vec->x;
}


float
vec2_get_y(const vec2 vec)
{
  const detail::internal_vec2 *internal_vec = reinterpret_cast<const detail::internal_vec2*>(&vec);
  return internal_vec->y;
}


void
vec2_to_array(const vec2 a, float *out_array)
{
  out_array[0] = vec2_get_x(a);
  out_array[1] = vec2_get_y(a);
}


vec2
vec2_add(const vec2 a, const vec2 b)
{
  const detail::internal_vec2 *vec_a = reinterpret_cast<const detail::internal_vec2*>(&a);
  const detail::internal_vec2 *vec_b = reinterpret_cast<const detail::internal_vec2*>(&b);

  return vec2_init(vec_a->x + vec_b->x, vec_a->y + vec_b->y);
}


vec2
vec2_subtract(const vec2 a, const vec2 b)
{
  const detail::internal_vec2 *vec_a = reinterpret_cast<const detail::internal_vec2*>(&a);
  const detail::internal_vec2 *vec_b = reinterpret_cast<const detail::internal_vec2*>(&b);

  return vec2_init(vec_a->x - vec_b->x, vec_a->y - vec_b->y);
}


vec2
vec2_multiply(const vec2 a, const vec2 b)
{
  const detail::internal_vec2 *vec_a = reinterpret_cast<const detail::internal_vec2*>(&a);
  const detail::internal_vec2 *vec_b = reinterpret_cast<const detail::internal_vec2*>(&b);

  return vec2_init(vec_a->x * vec_b->x, vec_a->y * vec_b->y);
}


vec2
vec2_divide(const vec2 a, const vec2 b)
{
  const detail::internal_vec2 *vec_a = reinterpret_cast<const detail::internal_vec2*>(&a);
  const detail::internal_vec2 *vec_b = reinterpret_cast<const detail::internal_vec2*>(&b);

  // Divide by zero check.
  assert(vec_b->x != 0 && vec_b->y != 0);

  return vec2_init(vec_a->x / vec_b->x, vec_a->y / vec_b->y);
}


vec2
vec2_lerp(const vec2 start, const vec2 end, const float dt)
{
  const vec2 difference = vec2_subtract(end, start);
  const vec2 scaled     = vec2_scale(difference, dt);
  const vec2 position   = vec2_add(start, scaled);

  return position;
}


vec2
vec2_scale(const vec2 a, const float scale)
{
  const vec2 scale_vec = vec2_init(scale);
  return vec2_multiply(a, scale_vec);
}


vec2
vec2_normalize(const vec2 a)
{
  const float length = vec2_length(a);

  assert(length != 0); // Don't pass zero vectors. (0,0);

  return vec2_scale(a, (1.f / length));
}


float
vec2_length(const vec2 a)
{
  const detail::internal_vec2 *vec_a = reinterpret_cast<const detail::internal_vec2*>(&a);
  const float x = vec_a->x * vec_a->x + vec_a->y * vec_a->y;

  return sqrt(x);
}


float
vec2_cross(const vec2 a, const vec2 b)
{
  return (vec2_get_x(a) * vec2_get_y(b)) -
         (vec2_get_y(a) * vec2_get_x(b));
}


float
vec2_dot(const vec2 a, const vec2 b)
{
  return (vec2_get_x(a) * vec2_get_x(b)) +
         (vec2_get_y(a) * vec2_get_y(b));
}


bool
vec2_is_equal(const vec2 a, const vec2 b)
{
	return
  (
    (vec2_get_x(a) == vec2_get_x(b))
    &&
    (vec2_get_y(a) == vec2_get_y(b))
  );
}


bool
vec2_is_not_equal(const vec2 a, const vec2 b)
{
	return !vec2_is_equal(a, b);
}


bool
vec2_is_near(const vec2 a, const vec2 b, const float error)
{
  return(
    is_near(vec2_get_x(a), vec2_get_x(b), error)
    &&
    is_near(vec2_get_y(a), vec2_get_y(b), error)
  );
}


bool
vec2_is_not_near(const vec2 a, const vec2 b, const float error)
{
	return !vec2_is_near(a, b, error);
}


} // ns


#endif // math on fpu
#endif // inc guard
