#include "Ray.h"

namespace raytracer
{
	vec3 Ray::getPoint(float t) const
	{
		return eye + dir * t;
	}

	Ray::Ray(vec3 eye, vec3 dir, float tMin, float tMax)
		: eye(eye), dir(dir), tMin(tMin), tMax(tMax)
	{
	}

	Ray::Ray()
		: tMin(T_MIN), tMax(T_MAX)
	{
	}
}