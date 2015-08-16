#pragma once

#include "../utils/Mathf.h"
#include "Collision.h"
#include "primitives/Ray.h"

namespace raytracer 
{
	class Shape
	{
	protected:
		Position position;
		mat4 transforms, invTransforms, invTranspTransforms;
	public:
		bool isTransformed;

		virtual Collision	findCollisionTo(const Ray &ray) const = 0;

		virtual void		transform(mat4 transforms);

		virtual Position	getPosition() const;
		virtual	vec2		computeUVCoords(const Collision &c) const;

							Shape(Position position);
		virtual				~Shape();
	};
}