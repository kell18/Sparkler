#pragma once

#include <glm/glm.hpp>
#include "Point.h"

using namespace glm;

namespace raytracer
{
	using Position = tvec3<float, mediump>;
	using Direction = tvec3<float, highp>;

	float dot(const Direction &d, const Position& p);
	Direction cross(const Direction &d, const Position& p);

	Direction operator*(const mat4& m, const Direction& d);
	Direction operator+(const Direction &d, const Position& p);
	Direction operator-(const Direction &d, const Position& p);
	Direction operator*(const Direction &d, const Position& p);
	Direction operator/(const Direction &d, const Position& p);
}