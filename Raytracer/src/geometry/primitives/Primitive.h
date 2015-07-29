#pragma once

#include "glm/glm.hpp"

#include "../Material.h"
#include "../Collision.h"
#include "Ray.h"

using namespace glm;

namespace raytracer
{
	class Primitive
	{
	protected:
		mat4 transforms, invTransforms, invTranspTransforms;

	public:
		bool isTransformed;
		vec3 position;
		Material material;

		// Todo: May be rename to collision
		virtual Collision	findIntersectionWith(const Ray &ray) const = 0;

		void				transform(mat4 transforms);

							Primitive(vec3 position, Material material);
		virtual				~Primitive();
	};

}
