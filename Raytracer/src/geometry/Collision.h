#pragma once

#include "Material.h"

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
		vec3 primitivePos;
	};
}
