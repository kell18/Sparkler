#include "Raytracer.h"

namespace raytracer
{
	Color Raytracer::findColor(const Ray &ray, int depth, float refractInd)
	{
		DisplayObject *dObject;
		Collision c = findNearestCollision(ray, dObject);
		if (c.isFind) {
			return dObject->findSurfaceColor(c, refractInd, depth);
		} else {
			return World::getActiveScene()->bgColor;
		}
	}

	Collision Raytracer::findNearestCollision(const Ray &ray, DisplayObject *&outDObject)
	{
		Collision nearest;
		Collision current;
		nearest.isFind = false;
		nearest.distance = FLT_MAX;
		vector<DisplayObject*> &dObjects = World::getActiveScene()->findNearestObjects(ray);
		for (auto dObject = dObjects.begin(); dObject != dObjects.end(); ++dObject) {
			current = (*dObject)->shape->findCollisionTo(ray); // TODO: Unused dot product computes here
			if (current.isFind && current.distance < nearest.distance) {
				nearest = current;
				outDObject = *dObject;
			}
		}
		return nearest;
	}


	Collision Raytracer::findAnyCollision(const Ray & ray, DisplayObject *&outDObject)
	{
		Collision c;
		vector<DisplayObject*> &dObjects = World::getActiveScene()->findNearestObjects(ray);
		for (size_t i = 0, len = dObjects.size(); i < len; ++i) {
			outDObject = dObjects[i];
			c = outDObject->shape->findCollisionTo(ray);
			if (c.isFind) {
				return c;
			}
		}
		return c;
	}
}
