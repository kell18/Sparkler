#pragma once

#include <glm/glm.hpp>

#include "../../utils/Constants.h"
#include "Primitive.h"
#include "Ray.h"
#include "../TexturedObject.h"
#include "../Collision.h"
#include "../Material.h"

using namespace glm;

namespace raytracer 
{
	
	class Rectangle : public Primitive, public TexturedObject
	{
	public:
		vec3 normal;
		vec3 a, b;
		vec3 aNorm, bNorm;
		float aLength, bLength;
		float aLengthSqr, bLengthSqr;

		virtual Collision	findIntersectionWith(const Ray &ray) const;

		virtual Color		getTexelColor(const vec3 &point) const;

							Rectangle(vec3 position, vec3 a, vec3 b, Material material);

	};

}