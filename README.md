# Math

[![Build Status](https://travis-ci.org/republic-of-almost/math.svg?branch=master)](https://travis-ci.org/republic-of-almost/math)
 [![Discord Channel](https://img.shields.io/badge/discord-republic_of_almost-738bd7.svg)](https://discord.gg/DU3s4fS) 
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](#)

This is a header only math library that built up in my hobby projects. I've extracted it and put it up here for anybody who wants it use it. Its a no-nonsense floating point math library.


## Support For
floating point vector types (2,3 and 4), floating point matrix types (3x3 and 4x4), floating point quaternion type, and some general math operations.


## Quick Guid

Very quick examples.

### Vectors

```cpp
const math::vec3 vec_a = math::vec3_init(1.f,2.f,3.f);
const math::vec3 vec_b = math::vec3_init(1.f,2.f,3.f);
const math::vec3 vec_c = math::vec3_add(vec_a, vec_b);
```

### Quaternions

```cpp
const math::vec3 axis = math::vec3_init(1.f,0.f,0.f);
const float angle = 0.12f;
const math::quat = math::quat_init_with_axis_angle(axis, angle);
```


### Getting Components

While the type may be a struct its recomended you get the value using the interface.

```cpp
const math::vec3 vec_a = math::vec3_init(1.f,2.f,3.f);
const float x = math::vec3_get_x(vec_a);

const math::quat = math::quat_init_with_axis_angle(axis, angle);
const float w = math::quat_get_w(quat);
```

Or shorthand

```cpp
const float x = math::get_x(vec_a);
const float w = math::get_w(quat);
```

## SIMD Support

There is partial SIMD support. To enable it, its recomeneded you build your project with preprocessor definition `MATH_USE_SIMD`

Type | SIMD
-----|-----
vec2 | YES
vec3 | YES
vec4 | YES
mat3 | NO
mat4 | NO


## License
MIT

