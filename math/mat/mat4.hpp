#ifndef MATRIX44_INCLUDED_45952EA8_98A0_40E4_8677_AE79A577E975
#define MATRIX44_INCLUDED_45952EA8_98A0_40E4_8677_AE79A577E975


/*
  Matrix 44
  Through out this library we consider a 4x4 matrix as a 
  world matrix.
*/


#include "mat_types.hpp"
#include "mat3.hpp"
#include "../vec/vec4.hpp"
#include <array>
#include <assert.h>


namespace math {


// Constants
MATH_MAT4_INLINE mat4                       mat4_id();
MATH_MAT4_INLINE mat4                       mat4_zero();

// Init
MATH_MAT4_INLINE mat4                       mat4_init(); // will return an id array
MATH_MAT4_INLINE mat4                       mat4_init(const float x);
MATH_MAT4_INLINE mat4                       mat4_init_with_mat3(const mat3 sub_matrix);
MATH_MAT4_INLINE mat4                       mat4_init_with_array(const float arr[]);
MATH_MAT4_INLINE mat4                       mat4_init_with_array(const std::array<float, 16> &array);

// Generate affine/special transformation matrices.
MATH_MAT4_INLINE mat4                       mat4_lookat(const vec3 eye_position, const vec3 look_at_position, const vec3 up);
MATH_MAT4_INLINE mat4                       mat4_projection(const float width, const float height, const float near_plane, const float far_plane, const float fov);
MATH_MAT4_INLINE mat4                       mat4_orthographic(const float width, const float height, const float near_plane,  const float far_plane);
MATH_MAT4_INLINE mat4                       mat4_scale(const vec3 scale);
MATH_MAT4_INLINE mat4                       mat4_scale(const float x, const float y, const float z);
MATH_MAT4_INLINE mat4                       mat4_translate(const vec3 move);
MATH_MAT4_INLINE mat4                       mat4_translate(const float x, const float y, const float z);
MATH_MAT4_INLINE mat4                       mat4_rotate_around_axis(const vec3 axis, const float radians);

// Operations
MATH_MAT4_INLINE mat4                       mat4_add(const mat4 &lhs, const mat4 &rhs);
MATH_MAT4_INLINE mat4                       mat4_subtract(const mat4 &lhs, const mat4 &rhs);
MATH_MAT4_INLINE mat4                       mat4_multiply(const float val, const mat4 &b);
MATH_MAT4_INLINE vec4                       mat4_multiply(const vec4 vec, const mat4 &b);
MATH_MAT4_INLINE mat4                       mat4_multiply(const mat4 &lhs, const mat4 &rhs);
MATH_MAT4_INLINE mat4                       mat4_multiply(const mat4 &one, const mat4 &two, const mat4 &three); //!< Handy for WVP type multiplications.

// Transform matrices into other forms
MATH_MAT4_INLINE mat4                       mat4_get_transpose(const mat4 &a);
MATH_MAT4_INLINE mat4                       mat4_get_inverse(const mat4 &a);
MATH_MAT4_INLINE float                      mat4_get_determinant(const mat4 &a);
MATH_MAT4_INLINE mat4                       mat4_get_scale(const mat4 &a, const vec3 scale);
// Get/Set information
MATH_MAT4_INLINE float                      mat4_get(const mat4 &mat, const uint32_t row, const uint32_t col);
MATH_MAT4_INLINE float                      mat4_get(const mat4 &mat, const uint32_t i);
MATH_MAT4_INLINE void                       mat4_set(mat4 &mat, const uint32_t row, const uint32_t col, const float set);
MATH_MAT4_INLINE mat3                       mat4_get_sub_mat3(const mat4 &a);
MATH_MAT4_INLINE vec3                       mat4_get_position(const mat4 &a);
MATH_MAT4_INLINE vec3                       mat4_get_scale(const mat4 &a);
MATH_MAT4_INLINE const float*               mat4_get_data(const mat4 &mat);

MATH_MAT4_INLINE void                       mat4_to_array(const mat4 &m, float *array);
MATH_MAT4_INLINE std::array<float, 16>      mat4_to_array(const mat4 &m);


// Impl

namespace detail
{
  struct internal_mat4
  {
    float data[16];
  };

}


mat4
mat4_id()
{
  const float id_array[16] = {
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f,
  };

  return mat4_init_with_array(id_array);
}


mat4
mat4_zero()
{
  const float zero_array[16] = {
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 0.f, 0.f, 0.f,
  };

  return mat4_init_with_array(zero_array);
}


mat4
mat4_init()
{
  return mat4_id();
}


mat4
mat4_init(const float x)
{
  float array[16];
  std::fill_n(array, 16, x);

  return mat4_init_with_array(array);
}


mat4
mat4_init_with_mat3(const mat3 sub_matrix)
{
  //TODO: Get data directly!
  const float mat_data[16] = {
    mat3_get(sub_matrix, 0), mat3_get(sub_matrix, 1), mat3_get(sub_matrix, 2), 0.f,
    mat3_get(sub_matrix, 3), mat3_get(sub_matrix, 4), mat3_get(sub_matrix, 5), 0.f,
    mat3_get(sub_matrix, 6), mat3_get(sub_matrix, 7), mat3_get(sub_matrix, 8), 0.f,
    0.f, 0.f, 0.f, 0.f,
  };
  
  return mat4_init_with_array(mat_data);
}


mat4
mat4_init_with_array(const float array[])
{
  mat4 return_mat;
  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&return_mat);

  memcpy(internal_mat->data, array, sizeof(internal_mat->data));
  
  return return_mat;
}


mat4
mat4_init_with_array(const std::array<float, 16> &array)
{
  return mat4_init_with_array(array.data());
}


mat4
mat4_lookat(const vec3 eye_position, const vec3 look_at_position, const vec3 up)
{
  const vec3 z_axis = vec3_normalize(vec3_subtract(look_at_position, eye_position));
  const vec3 x_axis = vec3_normalize(vec3_cross(z_axis, up));
  const vec3 y_axis = vec3_cross(x_axis, z_axis);

  const float array_mat[16] =
  {
    vec3_get_x(x_axis),
    vec3_get_x(y_axis),
    -vec3_get_x(z_axis),
    0.f,

    vec3_get_y(x_axis),
    vec3_get_y(y_axis),
    -vec3_get_y(z_axis),
    0.f,

    vec3_get_z(x_axis),
    vec3_get_z(y_axis),
    -vec3_get_z(z_axis),
    0.f,

    -(vec3_dot(x_axis, eye_position)),
    -(vec3_dot(y_axis, eye_position)),
    +(vec3_dot(z_axis, eye_position)),
    1.f,
  };

  return mat4_init_with_array(array_mat);
}


mat4
mat4_projection(const float width, const float height, const float near_plane, const float far_plane, const float fov)
{
  const float aspect_ratio = width / height;
  const float one_over_tan_half_fov = 1.f / math::tan(fov * 0.5f);
  const float plane_diff = far_plane - near_plane;

  //mat4 return_mat = mat4_zero();
  const float proj_mat[16] =
  {
    one_over_tan_half_fov / aspect_ratio,
    0.f,
    0.f,
    0.f,

    0.f,
    one_over_tan_half_fov,
    0.f,
    0.f, 

    0.f,
    0.f,
    -(far_plane + near_plane) / plane_diff,
    -1.f,

    0.f,
    0.f,
    -(2.f * far_plane * near_plane) / plane_diff,
    0.f,

 };

 return mat4_init_with_array(proj_mat);
}


mat4
mat4_orthographic(const float width, const float height, const float near_plane, const float far_plane)
{
  const float depth = far_plane - near_plane;
  assert(depth > 0);

  const float ortho_mat[16] = 
  {
    2.f / width,
    0.f,
    0.f,
    0.f,

    0.f,
    2.f / height,
    0.f,
    0.f,
    
    0.f,
    0.f,
    1.f / depth,
    -near_plane / depth,
 
    0.f,
    0.f,
    0.f,
    1.f,
  };

  return mat4_init_with_array(ortho_mat);
}


// Operations
mat4
mat4_add(const mat4 &lhs, const mat4 &rhs)
{
  const detail::internal_mat4 *left = reinterpret_cast<const detail::internal_mat4*>(&lhs);
  const detail::internal_mat4 *right = reinterpret_cast<const detail::internal_mat4*>(&rhs);

  mat4 return_mat; 
  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&return_mat);

  for(int i = 0; i < 16; ++i)
  {
    internal_mat->data[i] = left->data[0] + right->data[0];
  }

  return return_mat;
}


mat4
mat4_subtract(const mat4 &lhs, const mat4 &rhs)
{
  const detail::internal_mat4 *left = reinterpret_cast<const detail::internal_mat4*>(&lhs);
  const detail::internal_mat4 *right = reinterpret_cast<const detail::internal_mat4*>(&rhs);

  mat4 return_mat; 
  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&return_mat);

  for(uint32_t i = 0; i < 16; ++i)
  {
    internal_mat->data[i] = left->data[0] - right->data[0];
  }

  return return_mat;
}


mat4
mat4_scale(const vec3 scale_vec)
{
  return mat4_scale(vec3_get_x(scale_vec), vec3_get_y(scale_vec), vec3_get_z(scale_vec));
}


mat4
mat4_scale(const float x, const float y, const float z)
{
  mat4 return_mat = mat4_id();
  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&return_mat);
  
  internal_mat->data[0]  = x;
  internal_mat->data[5]  = y;
  internal_mat->data[10] = z;
  
  return return_mat;
}


mat4
mat4_multiply(const float lhs, const mat4 &rhs)
{
  mat4 multiply_mat = mat4_init(lhs);
  
  return mat4_multiply(multiply_mat, rhs);
}


vec4
mat4_multiply(const vec4 lhs, const mat4 &rhs)
{
  const detail::internal_mat4 *right = reinterpret_cast<const detail::internal_mat4*>(&rhs);
  float result[4];

  for(uint32_t i = 0; i < 4; ++i)
  {
    const vec4 dot_vec = vec4_init(right->data[i + 0],
                                   right->data[i + 4],
                                   right->data[i + 8],
                                   right->data[i + 12]);

    result[i] = vec4_dot(lhs, dot_vec);
  }

  return vec4_init_with_array(result);
}


mat4
mat4_multiply(const mat4 &one, const mat4 &two, const mat4 &three)
{
  return mat4_multiply(mat4_multiply(one, two), three);
}


mat4
mat4_multiply(const mat4 &lhs, const mat4 &rhs)
{
  const detail::internal_mat4 *left  = reinterpret_cast<const detail::internal_mat4*>(&lhs);
  const detail::internal_mat4 *right = reinterpret_cast<const detail::internal_mat4*>(&rhs);

  mat4 return_mat = mat4_id();
  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&return_mat);

  for(uint32_t i = 0; i < 16; ++i)
  {
    // Starting index for data.
    const uint32_t row = (i / 4) * 4;
    const uint32_t col = (i % 4);

    const vec4 row_vec = vec4_init(left->data[row + 0],
                                   left->data[row + 1],
                                   left->data[row + 2],
                                   left->data[row + 3]);

    const vec4 col_vec = vec4_init(right->data[col + 0],
                                   right->data[col + 4],
                                   right->data[col + 8],
                                   right->data[col + 12]);

    const float dot = vec4_dot(row_vec, col_vec);
    
    internal_mat->data[i] = dot;
  }

  return return_mat;
}


mat4
mat4_get_transpose(const mat4 &to_transpose)
{
  const detail::internal_mat4 *transpose_data = reinterpret_cast<const detail::internal_mat4*>(&to_transpose);
  
  const float mat_transpose[16]
  {
    transpose_data->data[0],  transpose_data->data[4],  transpose_data->data[8],  transpose_data->data[12],
    transpose_data->data[1],  transpose_data->data[5],  transpose_data->data[9],  transpose_data->data[13],
    transpose_data->data[2],  transpose_data->data[6],  transpose_data->data[10], transpose_data->data[14],
    transpose_data->data[3],  transpose_data->data[7],  transpose_data->data[11], transpose_data->data[15],
  };
  
  return mat4_init_with_array(mat_transpose);
}


mat4
mat4_get_inverse(const mat4 &to_inverse)
{
  const detail::internal_mat4 *to_i = reinterpret_cast<const detail::internal_mat4*>(&to_inverse);
  
  float inverse[16]
  {
    to_i->data[5]  * to_i->data[10] * to_i->data[15] -
    to_i->data[5]  * to_i->data[11] * to_i->data[14] -
    to_i->data[9]  * to_i->data[6]  * to_i->data[15] + 
    to_i->data[9]  * to_i->data[7]  * to_i->data[14] +
    to_i->data[13] * to_i->data[6]  * to_i->data[11] - 
    to_i->data[13] * to_i->data[7]  * to_i->data[10],

    -to_i->data[4]  * to_i->data[10] * to_i->data[15] +
    to_i->data[4]  * to_i->data[11] * to_i->data[14] +
    to_i->data[8]  * to_i->data[6]  * to_i->data[15] - 
    to_i->data[8]  * to_i->data[7]  * to_i->data[14] - 
    to_i->data[12] * to_i->data[6]  * to_i->data[11] + 
    to_i->data[12] * to_i->data[7]  * to_i->data[10],

    to_i->data[4]  * to_i->data[9] * to_i->data[15] -
    to_i->data[4]  * to_i->data[11] * to_i->data[13] -
    to_i->data[8]  * to_i->data[5] * to_i->data[15] + 
    to_i->data[8]  * to_i->data[7] * to_i->data[13] + 
    to_i->data[12] * to_i->data[5] * to_i->data[11] - 
    to_i->data[12] * to_i->data[7] * to_i->data[9],

    -to_i->data[4]  * to_i->data[9] * to_i->data[14] +
    to_i->data[4]  * to_i->data[10] * to_i->data[13] +
    to_i->data[8]  * to_i->data[5] * to_i->data[14] - 
    to_i->data[8]  * to_i->data[6] * to_i->data[13] - 
    to_i->data[12] * to_i->data[5] * to_i->data[10] + 
    to_i->data[12] * to_i->data[6] * to_i->data[9],

    -to_i->data[1]  * to_i->data[10] * to_i->data[15] +
    to_i->data[1]  * to_i->data[11] * to_i->data[14] +
    to_i->data[9]  * to_i->data[2] * to_i->data[15] - 
    to_i->data[9]  * to_i->data[3] * to_i->data[14] - 
    to_i->data[13] * to_i->data[2] * to_i->data[11] + 
    to_i->data[13] * to_i->data[3] * to_i->data[10],

    to_i->data[0]  * to_i->data[10] * to_i->data[15] - 
    to_i->data[0]  * to_i->data[11] * to_i->data[14] - 
    to_i->data[8]  * to_i->data[2] * to_i->data[15] + 
    to_i->data[8]  * to_i->data[3] * to_i->data[14] + 
    to_i->data[12] * to_i->data[2] * to_i->data[11] - 
    to_i->data[12] * to_i->data[3] * to_i->data[10],

    -to_i->data[0]  * to_i->data[9] * to_i->data[15] + 
    to_i->data[0]  * to_i->data[11] * to_i->data[13] + 
    to_i->data[8]  * to_i->data[1] * to_i->data[15] - 
    to_i->data[8]  * to_i->data[3] * to_i->data[13] - 
    to_i->data[12] * to_i->data[1] * to_i->data[11] + 
    to_i->data[12] * to_i->data[3] * to_i->data[9],

    to_i->data[0]  * to_i->data[9] * to_i->data[14] - 
    to_i->data[0]  * to_i->data[10] * to_i->data[13] - 
    to_i->data[8]  * to_i->data[1] * to_i->data[14] + 
    to_i->data[8]  * to_i->data[2] * to_i->data[13] + 
    to_i->data[12] * to_i->data[1] * to_i->data[10] - 
    to_i->data[12] * to_i->data[2] * to_i->data[9],

    to_i->data[1]  * to_i->data[6] * to_i->data[15] - 
    to_i->data[1]  * to_i->data[7] * to_i->data[14] - 
    to_i->data[5]  * to_i->data[2] * to_i->data[15] + 
    to_i->data[5]  * to_i->data[3] * to_i->data[14] + 
    to_i->data[13] * to_i->data[2] * to_i->data[7] - 
    to_i->data[13] * to_i->data[3] * to_i->data[6],

    -to_i->data[0]  * to_i->data[6] * to_i->data[15] + 
    to_i->data[0]  * to_i->data[7] * to_i->data[14] + 
    to_i->data[4]  * to_i->data[2] * to_i->data[15] - 
    to_i->data[4]  * to_i->data[3] * to_i->data[14] - 
    to_i->data[12] * to_i->data[2] * to_i->data[7] + 
    to_i->data[12] * to_i->data[3] * to_i->data[6],

    to_i->data[0]  * to_i->data[5] * to_i->data[15] - 
    to_i->data[0]  * to_i->data[7] * to_i->data[13] - 
    to_i->data[4]  * to_i->data[1] * to_i->data[15] + 
    to_i->data[4]  * to_i->data[3] * to_i->data[13] + 
    to_i->data[12] * to_i->data[1] * to_i->data[7] - 
    to_i->data[12] * to_i->data[3] * to_i->data[5],

    -to_i->data[0]  * to_i->data[5] * to_i->data[14] + 
     to_i->data[0]  * to_i->data[6] * to_i->data[13] + 
     to_i->data[4]  * to_i->data[1] * to_i->data[14] - 
     to_i->data[4]  * to_i->data[2] * to_i->data[13] - 
     to_i->data[12] * to_i->data[1] * to_i->data[6] + 
     to_i->data[12] * to_i->data[2] * to_i->data[5],

    -to_i->data[1] * to_i->data[6] * to_i->data[11] + 
    to_i->data[1] * to_i->data[7] * to_i->data[10] + 
    to_i->data[5] * to_i->data[2] * to_i->data[11] - 
    to_i->data[5] * to_i->data[3] * to_i->data[10] - 
    to_i->data[9] * to_i->data[2] * to_i->data[7] + 
    to_i->data[9] * to_i->data[3] * to_i->data[6],

    to_i->data[0] * to_i->data[6] * to_i->data[11] - 
    to_i->data[0] * to_i->data[7] * to_i->data[10] - 
    to_i->data[4] * to_i->data[2] * to_i->data[11] + 
    to_i->data[4] * to_i->data[3] * to_i->data[10] + 
    to_i->data[8] * to_i->data[2] * to_i->data[7] - 
    to_i->data[8] * to_i->data[3] * to_i->data[6],

    -to_i->data[0] * to_i->data[5] * to_i->data[11] + 
     to_i->data[0] * to_i->data[7] * to_i->data[9] + 
     to_i->data[4] * to_i->data[1] * to_i->data[11] - 
     to_i->data[4] * to_i->data[3] * to_i->data[9] - 
     to_i->data[8] * to_i->data[1] * to_i->data[7] + 
     to_i->data[8] * to_i->data[3] * to_i->data[5],

    to_i->data[0] * to_i->data[5] * to_i->data[10] - 
    to_i->data[0] * to_i->data[6] * to_i->data[9] - 
    to_i->data[4] * to_i->data[1] * to_i->data[10] + 
    to_i->data[4] * to_i->data[2] * to_i->data[9] + 
    to_i->data[8] * to_i->data[1] * to_i->data[6] - 
    to_i->data[8] * to_i->data[2] * to_i->data[5],
  };
  
  const float determinant = to_i->data[0] * inverse[0] + to_i->data[1] * inverse[4] + to_i->data[2] * inverse[8] + to_i->data[3] * inverse[12];

  assert(determinant != 0);
  
  const float one_over_det = 1.f / determinant;
  
  for (auto &i : inverse)
  {
    i = i * one_over_det;
  }
  
  return mat4_init_with_array(inverse);
}


float
mat4_get_determinant(const mat4 &det)
{
  /*
    I J K l     0 1 2 3
    a b c d  =  4 5 6 7
    e f g h     8 9 10 11
    i j k l     12 13 14 15
  */

  const detail::internal_mat3 *mat = reinterpret_cast<const detail::internal_mat3*>(&det);

  const mat3 det_a_mat = mat3_init_with_array({mat->data[5], mat->data[6], mat->data[7],
                                               mat->data[9], mat->data[10], mat->data[11],
                                               mat->data[13], mat->data[14], mat->data[15]});
  const float det_a = mat->data[0] * mat3_get_determinant(det_a_mat);

  const mat3 det_b_mat = mat3_init_with_array({mat->data[4], mat->data[6], mat->data[7],
                                               mat->data[8], mat->data[10], mat->data[11],
                                               mat->data[12], mat->data[14], mat->data[15]});
  const float det_b = mat->data[1] * mat3_get_determinant(det_b_mat);

  const mat3 det_c_mat = mat3_init_with_array({mat->data[4], mat->data[5], mat->data[7],
                                               mat->data[8], mat->data[9], mat->data[11],
                                               mat->data[12], mat->data[13], mat->data[15]});
  const float det_c = mat->data[2] * mat3_get_determinant(det_c_mat);

  const mat3 det_d_mat = mat3_init_with_array({mat->data[4], mat->data[5], mat->data[6],
                                               mat->data[8], mat->data[9], mat->data[10],
                                               mat->data[12], mat->data[13], mat->data[14]});
  const float det_d = mat->data[3] * mat3_get_determinant(det_d_mat);

  return det_a - det_b + det_c - det_d;
}


mat4
mat4_translate(const vec3 move)
{
  return mat4_translate(vec3_get_x(move), vec3_get_y(move), vec3_get_z(move));
}


mat4
mat4_translate(const float x, const float y, const float z)
{
  mat4 translate_mat = mat4_id();
  detail::internal_mat4 *translate_me = reinterpret_cast<detail::internal_mat4*>(&translate_mat);

  translate_me->data[12] += x;
  translate_me->data[13] += y;
  translate_me->data[14] += z;

  return translate_mat;
}
  
  
mat4
mat4_rotate_around_axis(const vec3 axis, const float radians)
{
  mat4 rotation = mat4_id();
  detail::internal_mat4 *rotate_me = reinterpret_cast<detail::internal_mat4*>(&rotation);
  
  const math::vec3 norm_axis = math::vec3_normalize(axis);
  assert(math::vec3_length(norm_axis));

  const float sin_theta           = math::sin(radians);
  const float cos_theta           = math::cos(radians);
  const float one_minus_cos_theta = 1.f - cos_theta;
  
  const float x = vec3_get_x(norm_axis);
  const float y = vec3_get_y(norm_axis);
  const float z = vec3_get_z(norm_axis);
  
  rotate_me->data[0]  = cos_theta + ((x * x) * one_minus_cos_theta);
  rotate_me->data[1]  = ((x * y) * one_minus_cos_theta) - (z * sin_theta);
  rotate_me->data[2]  = ((x * z) * one_minus_cos_theta) + (y * sin_theta);
  rotate_me->data[3]  = 0;

  rotate_me->data[4]  = ((y * x) * one_minus_cos_theta) + (z * sin_theta);
  rotate_me->data[5]  = cos_theta + ((y * y) * one_minus_cos_theta);
  rotate_me->data[6]  = ((y * z) * one_minus_cos_theta) - (x * sin_theta);
  rotate_me->data[7]  = 0;

  rotate_me->data[8]  = ((z * x) * one_minus_cos_theta) - (y * sin_theta);
  rotate_me->data[9]  = ((z * y) * one_minus_cos_theta) + (x * sin_theta);
  rotate_me->data[10] = cos_theta + ((z * z) * one_minus_cos_theta);
  rotate_me->data[11] = 0;

  rotate_me->data[12] = 0;
  rotate_me->data[13] = 0;
  rotate_me->data[14] = 0;
  rotate_me->data[15] = 1;
  
  return rotation;
}


void
mat4_to_array(const mat4 &mat, float *out_array)
{
  const detail::internal_mat4 *internal_mat = reinterpret_cast<const detail::internal_mat4*>(&mat);
  memcpy(out_array, internal_mat->data, sizeof(float) * 16);
}


std::array<float, 16>
mat4_to_array(const mat4 &mat)
{
  std::array<float, 16> return_arr;
  
  mat4_to_array(mat, return_arr.data());

  return return_arr;
}


float
mat4_get(const mat4 &mat, const uint32_t row, const uint32_t col)
{
  assert(row < 4 && col < 4);

  const uint32_t i = (row * 4) + col;
  return mat4_get(mat, i);
}


float
mat4_get(const mat4 &mat, const uint32_t index)
{
  assert(index < 16);
  
  const detail::internal_mat4 *internal_mat = reinterpret_cast<const detail::internal_mat4*>(&mat);
  return internal_mat->data[index];
}

  
const float*
mat4_get_data(const mat4 &mat)
{
  const detail::internal_mat4 *internal_mat = reinterpret_cast<const detail::internal_mat4*>(&mat);
  return &(internal_mat->data[0]);
}

  
void
mat4_set(mat4 &mat, const uint32_t row, const uint32_t col, const float set)
{
  assert(row < 4 && col < 4);

  detail::internal_mat4 *internal_mat = reinterpret_cast<detail::internal_mat4*>(&mat);
  internal_mat->data[(row * 4) + col] = set;
}


mat3
mat4_get_sub_mat3(const mat4 &m)
{
  const detail::internal_mat4 *internal_mat = reinterpret_cast<const detail::internal_mat4*>(&m);
  
  const float mat_data[9] = {
    internal_mat->data[0], internal_mat->data[1], internal_mat->data[2],
    internal_mat->data[4], internal_mat->data[5], internal_mat->data[6],
    internal_mat->data[8], internal_mat->data[9], internal_mat->data[10],
  };
  
  return mat3_init_with_array(mat_data);
}

} // namespace


#endif // include guard
