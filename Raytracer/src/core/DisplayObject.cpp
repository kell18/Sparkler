#include "DisplayObject.h"

namespace raytracer 
{
	Color DisplayObject::findSurfaceColor(const Collision &c, const Ray& ray, 
		float ior, int depth) const
	{
		vec2 uvCoords;
		if (material->isTextured()) {
			uvCoords = shape->computeUVCoords(c);
		}
		return material->findSurfaceColor(c, ray, ior, depth, uvCoords);
	}

	DisplayObject::DisplayObject(Shape* shape, Material* material)
		: shape(shape), material(material)
	{
	}

	DisplayObject::~DisplayObject()
	{
		delete shape;
		delete material;
	}
}