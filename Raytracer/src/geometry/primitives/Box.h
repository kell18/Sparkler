#pragma once

#include <algorithm>
#include "../Shape.h"

namespace raytracer
{
	// NOTE: Unimplemented to the end
	class Box : Shape
	{
	protected:
		Position fromP, toP;
	public:
		virtual Collision	findCollisionTo(const Ray & ray) const override;

							Box(Position fromPoint, Position toPoint);
		virtual				~Box();
	};
}