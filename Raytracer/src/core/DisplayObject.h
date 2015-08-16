#pragma once

#include "materials/Material.h"
#include "../geometry/Shape.h"

namespace raytracer 
{
	class Material;
	class Shape;

	class DisplayObject
	{
	private: 
	public:
		// TODO: Make private
		Shape* shape;
		Material* material;

		Color		findSurfaceColor(const Collision &c, const Ray& ray, float ior, 
						int depth) const;
					DisplayObject(Shape* shape, Material* material);
					~DisplayObject();
	};
}