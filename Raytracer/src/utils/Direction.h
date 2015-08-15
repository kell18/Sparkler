#pragma once

#include <glm/glm.hpp>
#include "Point.h"

using namespace glm;

namespace raytracer
{
	class Point;

	using Direction = tvec3<float, highp>;

	float dot(const Direction &d, const Point& p);
	Direction cross(const Direction &d, const Point& p);

	Direction operator*(const mat4& m, const Direction& d);
	Direction operator+(const Direction &d, const Point& p);
	Direction operator-(const Direction &d, const Point& p);
	Direction operator*(const Direction &d, const Point& p);
	Direction operator/(const Direction &d, const Point& p);
}