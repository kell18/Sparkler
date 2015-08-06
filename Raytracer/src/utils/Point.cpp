#include "Point.h"

namespace raytracer 
{

	Point operator*(const mat4& m, Point& p) 
	{
		return Point(m[0][0] * p.x + m[1][0] * p.y + m[2][0] * p.z + m[3][0],
					 m[0][1] * p.x + m[1][1] * p.y + m[2][1] * p.z + m[3][1],
					 m[0][2] * p.x + m[1][2] * p.y + m[2][2] * p.z + m[3][2]);
	}

	float pointStuff(Point p)
	{
		return p.x;
	}

}