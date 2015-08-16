#pragma once

#include <type_traits>
#include "../../utils/Mathf.h"
#include <glm/gtx/transform.hpp>
#include "../Shape.h"
#include "../Collision.h"

using namespace glm;

namespace raytracer
{
	class Sphere : public Shape
	{
	public:
		float radius;

		virtual Collision	findCollisionTo(const Ray &ray) const override;

		virtual vec2		computeUVCoords(const Collision &c) const override;

							Sphere(Position position, float radius);
		virtual				~Sphere();
	};

}
