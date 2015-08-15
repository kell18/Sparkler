#pragma once

#include <algorithm>
#include "Primitive.h"

namespace raytracer
{
	// NOTE: Unimplemented to the end
	class Box : Primitive
	{
	protected:
		vec3 fromP, toP;
	public:
		virtual Collision	findIntersectionWith(const Ray & ray) const override;

							Box(vec3 fromPoint, vec3 toPoint, Material material);
	};
}