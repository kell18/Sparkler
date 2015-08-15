#pragma once

#include <type_traits>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Primitive.h"
#include "../TexturedObject.h"
#include "../Material.h"
#include "../Collision.h"

using namespace glm;

namespace raytracer
{
	class Sphere : public Primitive
	{
	public:
		float radius;

		virtual Collision	findIntersectionWith(const Ray &ray) const override;

		virtual Color		getTexelColor(const vec3 &pointNormal) const override;

							Sphere(vec3 position, float radius, Material material);
		virtual				~Sphere();
	};

}
