#pragma once

#include "../../utils/Mathf.h"
#include "Primitive.h"
#include "Ray.h"
#include "../TexturedObject.h"
#include "../Collision.h"
#include "../Material.h"

using namespace glm;

namespace raytracer 
{
	
	class Rectangle : public Primitive
	{
	private:
		vec3 normal;
		vec3 a, b;
		vec3 aNorm, bNorm;
		float aLength, bLength;
		float aLengthSqr, bLengthSqr;
	public:

		virtual Collision	findIntersectionWith(const Ray &ray) const override;
		virtual Color		getTexelColor(const vec3 &point) const override;

		vec3				getA() const;
		vec3				getB() const;

							Rectangle(vec3 position, vec3 a, vec3 b, Material material);

	};

}