#ifndef TO_STRING_INCLUDED_AA5F04E4_BDD9_4385_99F2_2C9E7210FDD6
#define TO_STRING_INCLUDED_AA5F04E4_BDD9_4385_99F2_2C9E7210FDD6


#include "../vec/vec.hpp"
#include "../mat/mat.hpp"
#include <string>


namespace math {


inline std::string to_string(const vec2 vec);
inline std::string to_string(const vec3 vec);
inline std::string to_string(const vec4 vec);
inline std::string to_string(const mat4 mat, const bool line_breaks = false);


//inline std::string
//to_string(const vec2 vec)
//{
//	const std::string x = std::to_string(vec2_get_x(vec));
//	const std::string y = std::to_string(vec2_get_y(vec));
//
//	return std::string("Vec2: " + x + ", " + y);
//}


//inline std::string
//to_string(const vec3 vec)
//{
//	const std::string x = std::to_string(vec3_get_x(vec));
//	const std::string y = std::to_string(vec3_get_y(vec));
//	const std::string z = std::to_string(vec3_get_z(vec));
//
//	return std::string("Vec3: " + x + ", " + y + ", " + z);
//}

inline std::string
to_string(const vec4 vec)
{
	const std::string x = std::to_string(vec4_get_x(vec));
	const std::string y = std::to_string(vec4_get_y(vec));
	const std::string z = std::to_string(vec4_get_z(vec));
	const std::string w = std::to_string(vec4_get_w(vec));

	return std::string("Vec4: " + x + ", " + y + ", " + z + ", " + w);
}


inline std::string
to_string(const mat4 mat, const bool line_breaks)
{
	const std::string row_break = line_breaks ? "\n" : ", ";

	const std::string row_1 = std::to_string(mat4_get(mat, 0, 0)) + ", " + std::to_string(mat4_get(mat, 0, 1)) + ", " + std::to_string(mat4_get(mat, 0, 2)) + ", " + std::to_string(mat4_get(mat, 0, 3)) + row_break;
	const std::string row_2 = std::to_string(mat4_get(mat, 1, 0)) + ", " + std::to_string(mat4_get(mat, 1, 1)) + ", " + std::to_string(mat4_get(mat, 1, 2)) + ", " + std::to_string(mat4_get(mat, 1, 3)) + row_break;
	const std::string row_3 = std::to_string(mat4_get(mat, 2, 0)) + ", " + std::to_string(mat4_get(mat, 2, 1)) + ", " + std::to_string(mat4_get(mat, 2, 2)) + ", " + std::to_string(mat4_get(mat, 2, 3)) + row_break;
	const std::string row_4 = std::to_string(mat4_get(mat, 3, 0)) + ", " + std::to_string(mat4_get(mat, 3, 1)) + ", " + std::to_string(mat4_get(mat, 3, 2)) + ", " + std::to_string(mat4_get(mat, 3, 3));

	const std::string title_break = line_breaks ? "\n" : " ";

	return std::string("Mat44:" + title_break + row_1 + row_2 + row_3 + row_4);
}


} // namespace


#endif // include guard