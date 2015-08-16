#pragma once

#include "../utils/Mathf.h"

namespace raytracer
{
	struct Collision
	{
		bool isFind;
		float distance;
		Position point;
		Direction normal;
	};
}




