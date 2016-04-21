#ifndef VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C
#define VECTOR_TYPES_INCLUDED_76A0D96A_8385_4283_9EA9_CF89D0D5A10C


/*
  Vector Types.
  These are the vector types in caffeine math.
*/


namespace math {


// To access the components you should go through the vector interface.

class vec4
{
  float data[4];
};

class vec3
{
  float data[3];
};

class vec2
{
  float data[2];
};

  
} // namespace


#endif // include guard