#pragma once

#include "../../utils/Mathf.h"
#include "Primitive.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Material.h"

using namespace glm;

namespace raytracer
{
	class Plane : public Primitive
	{
	protected:
		vec3 normal;
	public:

		virtual Collision	findIntersectionWith(const Ray &ray) const override;
		vec3				getNormal() const;
							Plane(vec3 position, vec3 normal, Material material);
		virtual				~Plane();
	};
}

