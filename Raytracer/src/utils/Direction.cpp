#include "Direction.h"

namespace raytracer
{
	float dot(const Direction &d, const Position& p)
	{
		return d.x * p.x + d.y *p.y + d.z *p.z;
	}

	Direction cross(const Direction &d, const Position& p)
	{
		return Direction(d.y * p.z - d.z * p.y,
						 d.z * p.x - d.x * p.z,
						 d.x * p.y - d.y * p.x);
	}

	Direction operator*(const mat4& m, const Direction& d)
	{
		return Direction(m[0][0] * d.x + m[1][0] * d.y + m[2][0] * d.z,
						 m[0][1] * d.x + m[1][1] * d.y + m[2][1] * d.z,
						 m[0][2] * d.x + m[1][2] * d.y + m[2][2] * d.z);
	}

	Direction operator+(const Direction &d, const Position& p)
	{
		return Direction(d.x + p.x, d.y + p.y, d.z + p.z);
	}

	Direction operator-(const Direction &d, const Position& p)
	{
		return Direction(d.x - p.x, d.y - p.y, d.z - p.z);
	}

	Direction operator*(const Direction &d, const Position& p)
	{
		return Direction(d.x * p.x, d.y * p.y, d.z * p.z);
	}

	Direction operator/(const Direction &d, const Position& p)
	{
		return Direction(d.x / p.x, d.y / p.y, d.z / p.z);
	}

}