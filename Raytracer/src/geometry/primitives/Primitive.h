#pragma once

#include "glm/glm.hpp"

#include "../Material.h"
#include "../Collision.h"
#include "../TexturedObject.h"
#include "Ray.h"

using namespace glm;

namespace raytracer
{
	class Primitive : public TexturedObject
	{
	protected:
		mat4 transforms, invTransforms, invTranspTransforms;
		vec3 position;
	public:
		bool isTransformed;
		Material material;

		// Todo: May be rename to collision
		virtual Collision	findIntersectionWith(const Ray &ray) const = 0;

		vec3				getPosition() const;
		void				transform(mat4 transforms);

							Primitive(vec3 position, Material material);
		virtual				~Primitive();
	};

}
