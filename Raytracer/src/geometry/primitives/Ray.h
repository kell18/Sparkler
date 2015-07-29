#pragma once

#include "glm/glm.hpp"
#include "FreeImage.h"

using namespace glm;

namespace raytracer
{
	class Ray
	{
	public:
		vec3	eye, dir;
		float	tMin, tMax;

		vec3	getPoint(float t) const;

				Ray(vec3 eye, vec3 dir, float tMin = 1e-4f, float tMax = 1000000.0f);
	};
}

