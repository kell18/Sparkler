#pragma once

#include "../../utils/Mathf.h"
#include "Primitive.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Material.h"

namespace raytracer
{
	class Plane : public Primitive
	{
	protected:
		Direction normal;
	public:

		virtual Collision	findIntersectionWith(const Ray &ray) const override;
		Direction			getNormal() const;
							Plane(Position position, Direction normal, Material material);
		virtual				~Plane();
	};
}

