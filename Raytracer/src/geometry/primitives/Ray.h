#pragma once

#include "../../utils/Mathf.h"

#define T_MIN 1e-4f
#define T_MAX 1000000.0f
#define SELF_COLLISION_AMEND 0.0001f

namespace raytracer
{
	class Ray
	{
	public:
		Position  eye; 
		Direction dir;
		float	  tMin, tMax;

		static Ray	BuildShifted(Position eye, Direction dir, float tMin = T_MIN, float tMax = T_MAX);

					Ray(Position eye, Direction dir, float tMin = T_MIN, float tMax = T_MAX);
					Ray();
	};
}

