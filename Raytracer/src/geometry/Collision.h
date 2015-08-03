#pragma once

#include "Material.h"
#include "primitives/Ray.h"

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
