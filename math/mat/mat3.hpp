#ifndef MATRIX33_INCLUDED_D6DCE389_FA7C_4C48_A303_C0EDC9A90C8B
#define MATRIX33_INCLUDED_D6DCE389_FA7C_4C48_A303_C0EDC9A90C8B


/*
  Matrix 33
  Through out this library we consider a 3x3 matrix as a 
  rotation and scale matrix specifically.
*/


#include "mat_types.hpp"
#include "../vec/vec3.hpp"
#include "../vec/vec2.hpp"
#include <array>
#include <cstring>


namespace math {


// Constants
inline mat3                       mat3_id();
inline mat3                       mat3_zero();

// Init
inline mat3                       mat3_init(); // will return an id array
inline mat3                       mat3_init(const float x);
inline mat3                       mat3_init_with_array(const float arr[]);
inline mat3                       mat3_init_with_array(const std::array<float, 9> &array);

// Operations
inline mat3                       mat3_add(const mat3 &lhs, const mat3 &rhs);
inline mat3                       mat3_subtract(const mat3 &lhs, const mat3 &rhs);
inline mat3                       mat3_scale(const float x, const float y);
inline mat3                       mat3_scale(const vec2 scale);
inline vec3                       mat3_multiply(const vec3 vec, const mat3 &b);
inline mat3                       mat3_multiply(const mat3 &lhs, const mat3 &rhs);

inline mat3                       mat3_translate(const vec2 vec); // no imp
inline mat3                       mat3_translate(const float x, const float y); // no imp
inline mat3                       mat3_rotation_from_euler(const float radians);

inline float                      mat3_get_determinant(const mat3 &a);

// Transform matrices into other forms
inline mat3                       mat3_get_transpose(const mat3 &a);
inline mat3                       mat3_get_inverse(const mat3 &a);
inline mat3                       mat3_get_scale(const mat3 &a, const vec3 scale);
inline void                       mat3_to_array(const mat3 &m, float *array);
inline std::array<float, 9>       mat3_to_array(const mat3 &m);

// Get/Set information
inline float                      mat3_get(const mat3 &mat, const uint32_t row, const uint32_t col);
inline float                      mat3_get(const mat3 &mat, const uint32_t i);
inline void                       mat3_set(mat3 &mat, const uint32_t row, const uint32_t col, const float set);
inline vec3                       mat3_get_scale(const mat3 &a);


// Impl

namespace detail
{
  struct internal_mat3
  {
    float data[9];
  };

}


mat3
mat3_id()
{
  const float id_array[9] = {
    1.f, 0.f, 0.f,
    0.f, 1.f, 0.f,
    0.f, 0.f, 1.f,
  };

  return mat3_init_with_array(id_array);
}


mat3
mat3_zero()
{
  const float zero_array[9] = {
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
  };

  return mat3_init_with_array(zero_array);
}


mat3
mat3_init()
{
  return mat3_id();
}


mat3
mat3_init(const float x)
{
  float array[9];
  std::fill_n(array, 9, x);
  
  return mat3_init_with_array(array);
}


mat3
mat3_init_with_array(const float array[])
{
  mat3 return_mat;
  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  memcpy(internal_mat->data, array, sizeof(internal_mat->data));
  
  return return_mat;
}


mat3
mat3_init_with_array(const std::array<float, 9> &array)
{
  return mat3_init_with_array(array.data());
}


// Operations
mat3
mat3_add(const mat3 &lhs, const mat3 &rhs)
{
  const detail::internal_mat3 *left  = reinterpret_cast<const detail::internal_mat3*>(&lhs);
  const detail::internal_mat3 *right = reinterpret_cast<const detail::internal_mat3*>(&rhs);

  mat3 return_mat; 
  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  for(uint32_t i = 0; i < 9; ++i)
  {
    internal_mat->data[i] = left->data[0] + right->data[0];
  }

  return return_mat;
}


mat3
mat3_subtract(const mat3 &lhs, const mat3 &rhs)
{
  const detail::internal_mat3 *left  = reinterpret_cast<const detail::internal_mat3*>(&lhs);
  const detail::internal_mat3 *right = reinterpret_cast<const detail::internal_mat3*>(&rhs);

  mat3 return_mat; 
  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  for(uint32_t i = 0; i < 9; ++i)
  {
    internal_mat->data[i] = left->data[0] - right->data[0];
  }

  return return_mat;
}


mat3
mat3_scale(const vec2 scale)
{
  return mat3_scale(vec2_get_x(scale), vec2_get_y(scale));
}


mat3
mat3_scale(const float x, const float y)
{
  mat3 return_mat = mat3_id();
  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  internal_mat->data[0] = x;
  internal_mat->data[4] = y;

  return return_mat;
}


vec3
mat3_multiply(const vec3 lhs, const mat3 &rhs)
{
  const detail::internal_mat3 *right = reinterpret_cast<const detail::internal_mat3*>(&rhs);
  __declspec(align(16)) float vec_data[9];

  for(uint32_t i = 0; i < 3; ++i)
  {
    const vec3 dot_vec = vec3_init(right->data[i + 0],
                                   right->data[i + 3],
                                   right->data[i + 6]);

    vec_data[i] = vec3_dot(lhs, dot_vec);
  }

  return vec3_init_with_array(vec_data);
}


mat3
mat3_multiply(const mat3 &lhs, const mat3 &rhs)
{
  const detail::internal_mat3 *left = reinterpret_cast<const detail::internal_mat3*>(&lhs);
  const detail::internal_mat3 *right = reinterpret_cast<const detail::internal_mat3*>(&rhs);

  mat3 return_mat = mat3_id();
  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  for(uint32_t i = 0; i < 9; ++i)
  {
    //[0,1,2,3] x [0,4,8,12]
    const uint32_t row = (i / 3) * 3;
    const uint32_t col = i % 3;

    const vec3 left_vec = vec3_init(left->data[row + 0],
                                    left->data[row + 1],
                                    left->data[row + 2]);

    const vec3 right_vec = vec3_init(right->data[col + 0],
                                     right->data[col + 3],
                                     right->data[col + 6]);

    const float dot = vec3_dot(left_vec, right_vec);
    internal_mat->data[i] = dot;
  }

  return return_mat;
}


mat3
mat3_rotation_from_euler(const float radians)
{
  mat3 return_mat = mat3_id();
  detail::internal_mat3 *mat = reinterpret_cast<detail::internal_mat3*>(&return_mat);

  mat->data[0] = +math::cos(radians);
  mat->data[1] = -math::sin(radians);
  mat->data[3] = +math::sin(radians);
  mat->data[4] = +math::cos(radians);

  return return_mat;
}


float
mat3_get_determinant(const mat3 &det)
{
  /*
    | i j k |   | 0 1 2 |
    | a b c | = | 3 4 5 |
    | d e f |   | 6 7 8 |
  */
  const detail::internal_mat3 *mat = reinterpret_cast<const detail::internal_mat3*>(&det);

  const float i = mat->data[0];
  const float j = mat->data[1];
  const float k = mat->data[2];

  const float a = mat->data[3];
  const float b = mat->data[4];
  const float c = mat->data[5];

  const float d = mat->data[6];
  const float e = mat->data[7];
  const float f = mat->data[8];

  return (i * (b * f - c * e)) +
         (j * (a * f - c * d)) -
         (k * (a * e - b * d));
}


mat3
mat3_get_transpose(const mat3 &m)
{
  const detail::internal_mat3 *mat = reinterpret_cast<const detail::internal_mat3*>(&m);
  
  const float transpose_data[9] = {
    mat->data[0], mat->data[3], mat->data[6],
    mat->data[1], mat->data[4], mat->data[7],
    mat->data[2], mat->data[5], mat->data[8],
  };
  
  return mat3_init_with_array(transpose_data);
}


float
mat3_get(const mat3 &mat, const uint32_t row, const uint32_t col)
{
  assert(row < 4 && col < 4);

  const uint32_t i = (row * 3) + col;
  return mat3_get(mat, i);
}


float
mat3_get(const mat3 &mat, const uint32_t index)
{
  assert(index < 9);
  
  const detail::internal_mat3 *internal_mat = reinterpret_cast<const detail::internal_mat3*>(&mat);
  return internal_mat->data[index];
}


void
mat3_set(mat3 &mat, const uint32_t row, const uint32_t col, const float set)
{
  assert(row < 4 && col < 4);

  detail::internal_mat3 *internal_mat = reinterpret_cast<detail::internal_mat3*>(&mat);
  internal_mat->data[(row * 4) + col] = set;
}




} // namespace


#endif // include guard