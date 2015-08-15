#pragma once

#include "../utils/Mathf.h"
#include "Material.h"

namespace raytracer
{
	struct Collision
	{
		bool isFind;
		float distance;

		Position point;
		Direction normal;

		Material material;
		Color texel;
	};
}
