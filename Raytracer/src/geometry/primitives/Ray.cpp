#include "Ray.h"

namespace raytracer
{
	Ray	Ray::BuildShifted(const Position &eye, const Direction &dir, float tMin, float tMax)
	{
		return Ray(eye + (dir * SELF_COLLISION_AMEND), dir, tMin, tMax);
	}

	Ray::Ray(Position eye, Direction dir, float tMin, float tMax)
		: eye(eye), dir(dir), tMin(tMin), tMax(tMax)
	{
	}

	Ray::Ray()
		: tMin(T_MIN), tMax(T_MAX)
	{
	}
}