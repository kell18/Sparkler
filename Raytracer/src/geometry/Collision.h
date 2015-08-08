#pragma once

#include "Material.h"
#include "primitives/Ray.h"

#define COLLISION_AMEND 0.00005f

namespace raytracer
{
	struct Collision
	{
		bool isFind;
		float distance;

		vec3 point;
		vec3 normal;

		Material material;
		Color texel;
	};
}
