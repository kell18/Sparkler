#pragma once

#include "../../utils/Mathf.h"
#include "Primitive.h"
#include "Plane.h"
#include "Ray.h"
#include "../Collision.h"
#include "../Material.h"

namespace raytracer
{

	class Triangle : public Primitive
	{
	protected:
		vec3 vert1, vert2, vert3;
		vec3 edge1, edge2;
		vec3 normal;
	public:

		virtual Collision	findIntersectionWith(const Ray &ray) const override;
		vec3				getNormal() const;
		vec3				getVert1() const;
		vec3				getVert2() const;
		vec3				getVert3() const;

							Triangle(vec3 vert1, vec3 vert2, vec3 vert3, Material material);
							~Triangle();
	};

}