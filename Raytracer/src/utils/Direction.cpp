#include "Direction.h"

namespace raytracer
{

	Direction operator*(const mat4& m, const Direction& d)
	{
		return Direction(m[0][0] * d.x + m[1][0] * d.y + m[2][0] * d.z,
						m[0][1] * d.x + m[1][1] * d.y + m[2][1] * d.z,
						m[0][2] * d.x + m[1][2] * d.y + m[2][2] * d.z);
	}

}