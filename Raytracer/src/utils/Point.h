#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace raytracer
{
	typedef vec3 Point;

	Point operator*(const mat4& m, Point& p);

	float pointStuff(Point p);

}

