#pragma once

#include <glm/glm.hpp>
#include "Direction.h"

using namespace glm;

namespace raytracer
{
	class Direction;

	using Point = tvec3<float, mediump>;

	float dot(const Point& p, const Direction &d);
	Direction cross(const Point& p, const Direction &d);

	Point operator*(const mat4& m, const Point& p);
	Point operator+(const Point& p, const Direction& d);
	Point operator-(const Point& p, const Direction& d);
	Point operator*(const Point& p, const Direction& d);
	Point operator/(const Point& p, const Direction& d);
}

