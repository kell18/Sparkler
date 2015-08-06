#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace raytracer
{

		using Direction = vec3;

		Direction operator*(const mat4& m, const Direction& d);


}