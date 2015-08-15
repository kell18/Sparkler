#pragma once

#include <algorithm>
#include "Primitive.h"

namespace raytracer
{
	// NOTE: Unimplemented to the end
	class Box : Primitive
	{
	protected:
		Position fromP, toP;
	public:
		virtual Collision	findIntersectionWith(const Ray & ray) const override;

							Box(Position fromPoint, Position toPoint, Material material);
	};
}