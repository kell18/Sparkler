#include "Mathf.h"

namespace raytracer 
{
	float Mathf::randFloat0to1()
	{
		return static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
	}

	bool Mathf::isAlmostZero(float a, float EPSILON) 
	{
		return a > -EPSILON && a < EPSILON;
	}

	bool Mathf::isAlmostEqual(float a, float b, float EPSILON)
	{
		float c = a - b;
		return c > -EPSILON && c < EPSILON;
	}
}
