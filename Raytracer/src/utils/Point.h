#pragma once

#include <glm/glm.hpp>
#include "Direction.h"

using namespace glm;

namespace raytracer
{
	using Direction = tvec3<float, highp>;
	using Position = tvec3<float, mediump>;

	float dot(const Position& p, const Direction &d);
	Direction cross(const Position& p, const Direction &d);

	Position operator*(const mat4& m, const Position& p);
	Position operator+(const Position& p, const Direction& d);
	Position operator-(const Position& p, const Direction& d);
	Position operator*(const Position& p, const Direction& d);
	Position operator/(const Position& p, const Direction& d);

	// TODO: point - point = dir
}

