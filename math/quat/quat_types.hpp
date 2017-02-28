#ifndef QUATERNION_TYPES_INCLUDED_14E724D5_7132_4778_9DAE_0215B606AF3C
#define QUATERNION_TYPES_INCLUDED_14E724D5_7132_4778_9DAE_0215B606AF3C


/*
  Quaternion type
*/


#include "../detail/detail.hpp"


_MATH_NS_OPEN


struct quat
{
	float data[4]; // x, y, z, w;
};


_MATH_NS_CLOSE


#endif // include guard
