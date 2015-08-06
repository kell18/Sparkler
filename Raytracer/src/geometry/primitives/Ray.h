#pragma once

#include "glm/glm.hpp"
#include "FreeImage.h"

#define T_MIN 1e-4f
#define T_MAX 1000000.0f

using namespace glm;

namespace raytracer
{
	class Ray
	{
	public:
		vec3	eye, dir;
		float	tMin, tMax;

		vec3	getPoint(float t) const;

				Ray(vec3 eye, vec3 dir, float tMin = T_MIN, float tMax = T_MAX);
				Ray();
	};
}

