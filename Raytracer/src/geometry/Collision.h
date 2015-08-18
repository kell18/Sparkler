#pragma once

#include "../utils/Mathf.h"
#include "primitives/Ray.h"

namespace raytracer
{
	class Collision
	{
	public:
		bool isFind;
		float distance;
		
		Position point;
		Direction normal;
		const Ray *ray;

						Collision();
						Collision(const Ray &ray);
	};
}




