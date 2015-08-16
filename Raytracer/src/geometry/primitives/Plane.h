#pragma once

#include "../../utils/Mathf.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Shape.h"

namespace raytracer
{
	class Plane : public Shape
	{
	protected:
		Direction normal;
	public:
		virtual Collision	findCollisionTo(const Ray &ray) const override;
		Direction			getNormal() const;

							Plane(Position position, Direction normal);
		virtual				~Plane();
	};
}

