#pragma once

#include "glm/glm.hpp"

using namespace glm;

namespace raytracer
{
	typedef vec3 point;
	typedef vec3 direction;
	typedef vec3 normal;

	point operator*(const mat4& m, const point& p);
	direction operator*(const mat4& m, direction& d);

	class Mathf
	{
	public:
	};
}

