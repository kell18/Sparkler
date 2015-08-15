#include "Point.h"

namespace raytracer 
{
	float dot(const Position& p, const Direction &d)
	{
		return p.x * d.x + p.y * d.y + p.z * d.z;
	}

	Direction cross(const Position& p, const Direction &d) 
	{
		return Direction(p.y * d.z - p.z * d.y,
						 p.z * d.x - p.x * d.z,
						 p.x * d.y - p.y * d.x);
	}

	Position operator*(const mat4& m, const Position& p)
	{
		return Position(m[0][0] * p.x + m[1][0] * p.y + m[2][0] * p.z + m[3][0],
					 m[0][1] * p.x + m[1][1] * p.y + m[2][1] * p.z + m[3][1],
					 m[0][2] * p.x + m[1][2] * p.y + m[2][2] * p.z + m[3][2]);
	}

	Position operator+(const Position& p, const Direction& d)
	{
		return Position(p.x + d.x, p.y + d.y, p.z + d.z);
	}

	Position operator-(const Position& p, const Direction& d)
	{
		return Position(p.x - d.x, p.y - d.y, p.z - d.z);
	}

	Position operator*(const Position& p, const Direction& d)
	{
		return Position(p.x * d.x, p.y * d.y, p.z * d.z);
	}

	Position operator/(const Position& p, const Direction& d)
	{
		return Position(p.x / d.x, p.y / d.y, p.z / d.z);
	}
}