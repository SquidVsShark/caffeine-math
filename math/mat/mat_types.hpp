#ifndef MATRIX_TYPES_INCLUDED_2460E1C2_10A1_4101_A23D_C5E683367E4A
#define MATRIX_TYPES_INCLUDED_2460E1C2_10A1_4101_A23D_C5E683367E4A


/*
  Matrix types
*/


#include "../detail/detail.hpp"


_MATH_NS_OPEN


class mat3
{
	float data[9];
};

class mat4
{
	float data[16];
};


_MATH_NS_CLOSE


#endif // include guard
