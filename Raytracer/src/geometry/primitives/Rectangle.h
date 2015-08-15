#pragma once

#include "../../utils/Mathf.h"
#include "Primitive.h"
#include "Ray.h"
#include "../TexturedObject.h"
#include "../Collision.h"
#include "../Material.h"

namespace raytracer 
{
	
	class Rectangle : public Primitive
	{
	private:
		Direction normal;
		Direction a, b;
		Direction aNorm, bNorm;
		float aLength, bLength;
		float aLengthSqr, bLengthSqr;
		float posDotNorm;
	public:

		virtual Collision	findIntersectionWith(const Ray &ray) const override;
		virtual Color		getTexelColor(const Collision &c) const override;

		Direction			getA() const;
		Direction			getB() const;

							Rectangle(Position position, Direction a, Direction b, Material material);

	};

}