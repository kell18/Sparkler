#pragma once

#include "../../utils/Mathf.h"
#include "../Shape.h"
#include "Ray.h"
#include "../Collision.h"

namespace raytracer 
{
	
	class Rectangle : public Shape
	{
	private:
		Direction normal;
		Direction a, b;
		Direction aNorm, bNorm;
		float aLength, bLength;
		float aLengthSqr, bLengthSqr;
		float posDotNorm;
	public:

		virtual Collision	findCollisionTo(const Ray &ray) const override;
		virtual vec2		computeUVCoords(const Collision &c) const override;

		Direction			getA() const;
		Direction			getB() const;

							Rectangle(Position position, Direction a, Direction b);

	};

}