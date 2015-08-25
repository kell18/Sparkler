#pragma once

#include "../../utils/Mathf.h"
#include "../Shape.h"
#include "Ray.h"
#include "../Collision.h"

namespace raytracer
{

	class Triangle : public Shape
	{
	protected:
		Position  vert1, vert2, vert3;
		Direction edge1, edge2;
		Direction normal;
	public:

		virtual Collision	findCollisionTo(const Ray &ray) const override;
		Direction			getNormal() const;
		Position			getVert1() const;
		Position			getVert2() const;
		Position			getVert3() const;

							Triangle(Position vert1, Position vert2, Position vert3);
	};

}