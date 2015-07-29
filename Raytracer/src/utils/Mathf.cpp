#include "Mathf.h"

namespace raytracer 
{
	point operator*(const mat4& m, const point& p) 
	{
		return point(m[0][0] * p.x + m[1][0] * p.y + m[2][0] * p.z + m[3][0],
					 m[0][1] * p.x + m[1][1] * p.y + m[2][1] * p.z + m[3][1],
					 m[0][2] * p.x + m[1][2] * p.y + m[2][2] * p.z + m[3][2]);
	}

	direction operator*(const mat4& m, direction& d) 
	{
		return direction(m[0][0] * d.x + m[1][0] * d.y + m[2][0] * d.z,
						 m[0][1] * d.x + m[1][1] * d.y + m[2][1] * d.z,
						 m[0][2] * d.x + m[1][2] * d.y + m[2][2] * d.z);
	} 
}
