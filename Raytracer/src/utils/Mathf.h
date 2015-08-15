#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cstdlib>

using namespace glm;

namespace raytracer
{
	static const float FLT_EPS = std::numeric_limits<float>::epsilon();

	class Mathf
	{
	public:
		static float	randFloat0to1();
		static bool		isAlmostZero(float a, float EPSILON = FLT_EPS);
		static bool		isAlmostEqual(float a, float b, float EPSILON = FLT_EPS);
	};
}

