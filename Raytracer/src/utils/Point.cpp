#include "Point.h"

namespace raytracer 
{
	float dot(const Point& p, const Direction &d)
	{
		// TODO: Count just here
		return glm::dot(vec3(p), vec3(d));
	}

	Direction cross(const Point& p, const Direction &d) 
	{
		// TODO: Count just here
		return glm::cross(vec3(p), vec3(d));
	}

	Point operator*(const mat4& m, const Point& p)
	{
		return Point(m[0][0] * p.x + m[1][0] * p.y + m[2][0] * p.z + m[3][0],
			m[0][1] * p.x + m[1][1] * p.y + m[2][1] * p.z + m[3][1],
			m[0][2] * p.x + m[1][2] * p.y + m[2][2] * p.z + m[3][2]);
	}

	Point operator+(const Point& p, const Direction& d)
	{
		return Point(p.x + d.x, p.y + d.y, p.z + d.z);
	}

	Point operator-(const Point& p, const Direction& d)
	{
		return Point(p.x - d.x, p.y - d.y, p.z - d.z);
	}

	Point operator*(const Point& p, const Direction& d)
	{
		return Point(p.x * d.x, p.y * d.y, p.z * d.z);
	}

	Point operator/(const Point& p, const Direction& d)
	{
		return Point(p.x / d.x, p.y / d.y, p.z / d.z);
	}
}