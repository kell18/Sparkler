#include "Mathf.h"

namespace raytracer 
{
	float Mathf::randFloat(float range) 
	{
		return (static_cast<float> (rand()) / FLT_RAND_MAX) * range;
	}

	float Mathf::randFloat(float from, float to) 
	{
		// TODO: Change to FLT_RAND_MAX
		return from + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) / (to - from));
	}

	float Mathf::randFloat0to1()
	{
		return static_cast<float> (rand()) / FLT_RAND_MAX;
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

	bool Mathf::isAlmostEqual(const vec3& a, const vec3& b, float EPSILON)
	{
		return isAlmostEqual(a.x, b.x, EPSILON) && 
			   isAlmostEqual(a.y, b.y, EPSILON) && 
			   isAlmostEqual(a.z, b.z, EPSILON);
	}

	std::ostream& operator<<(std::ostream& out, const vec3& g)
	{
		return out << glm::to_string(g);
	}
}
