#pragma once

#include "glm/glm.hpp"
#include "Primitive.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Material.h"

using namespace glm;

namespace raytracer
{
	class Plane : public Primitive
	{
	public:
		vec3 normal;

		virtual Collision	findIntersectionWith(const Ray &ray) const;

							Plane(vec3 position, vec3 normal, Material material);
		virtual				~Plane();
	};
}

