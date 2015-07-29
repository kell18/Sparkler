#pragma once

#include "glm/glm.hpp"
#include "Primitive.h"
#include "Plane.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Material.h"

namespace raytracer
{

	class Triangle : public Primitive
	{
	public:
		vec3 p1, p2, p3;
		vec3 v1, v2;
		vec3 normal;

		virtual Collision	findIntersectionWith(const Ray &ray) const;

							Triangle(vec3 p1, vec3 p2, vec3 p3, Material material);
							~Triangle();
	};

}