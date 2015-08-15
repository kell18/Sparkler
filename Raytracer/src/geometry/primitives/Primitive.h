#pragma once

#include "../../utils/Mathf.h"
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
		Position position;
	public:
		bool isTransformed;
		Material material;

		// Todo: May be rename to collision
		virtual Collision	findIntersectionWith(const Ray &ray) const = 0;

		Position				getPosition() const;
		void				transform(mat4 transforms);

							Primitive(Position position, Material material);
		virtual				~Primitive();
	};

}
