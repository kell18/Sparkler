#pragma once

#include <type_traits>
#include <glm/gtx/transform.hpp>

#include "Primitive.h"
#include "../../utils/Mathf.h"
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

		virtual Color		getTexelColor(const Collision &c) const override;

							Sphere(Position position, float radius, Material material);
		virtual				~Sphere();
	};

}
