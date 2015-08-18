#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cstdlib>
#include "Point.h"
#include "Direction.h"
#include "Color.h"

using namespace glm;

namespace raytracer
{

	// Precision values
	#ifndef FLT_EPS
	// Machine epsilon
	static const float FLT_EPS = std::numeric_limits<float>::epsilon();
	#endif
	// Most precise float epsilon (machine epsilon)
	static const float EXACT_EPS = FLT_EPS;
	// About epsilon (0.0001f)
	static const float ABOUT_EPS = 0.0001f;
	// Very rough epsilon (0.01f)
	static const float ROUGH_EPS = 0.01f;

	static const float FLT_RAND_MAX = static_cast<float> (RAND_MAX);
	
	class Mathf
	{
	public:
		static float	randFloat(float range);
		static float	randFloat(float from, float to);
		static float	randFloat0to1();

		static bool		isAlmostZero(float a, float EPSILON = FLT_EPS);
		static bool		isAlmostEqual(float a, float b, float EPSILON = FLT_EPS);
		static bool		isAlmostEqual(const vec3& a, const vec3& b, float EPSILON = FLT_EPS);
		
	};

	std::ostream& operator<<(std::ostream& out, const vec3& g);
}

