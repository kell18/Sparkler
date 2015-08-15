#pragma once

#include "glm/glm.hpp"
#include "FreeImage.h"

#define T_MIN 1e-4f
#define T_MAX 1000000.0f
#define SELF_COLLISION_AMEND 0.0001f

using namespace glm;

namespace raytracer
{
	class Ray
	{
	public:
		vec3	eye, dir;
		float	tMin, tMax;

		static Ray	BuildShifted(vec3 eye, vec3 dir, float tMin = T_MIN, float tMax = T_MAX);

					Ray(vec3 eye, vec3 dir, float tMin = T_MIN, float tMax = T_MAX);
					Ray();
	};
}

