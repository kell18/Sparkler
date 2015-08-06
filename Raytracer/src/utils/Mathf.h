#pragma once

#include "glm/glm.hpp"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"

#define TOTAL_INTERNAL_REFRACTION false

using namespace glm;

namespace raytracer
{

	class Mathf
	{
	public:
		static bool	computeRefractDir(vec3 eyeDir, const Collision &c, vec3& outRay, float &refrInd);
		static vec3	computeReflectDir(const vec3& eyePos, const vec3& point, const vec3& normal);
	};
}

