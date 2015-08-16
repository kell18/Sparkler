#pragma once

#include <vector>
#include <cfloat>

#include "../utils/Mathf.h"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"
#include "lights/Light.h"
#include "DisplayObject.h"
#include "Film.h"
#include "Scene.h"
#include "World.h"

using namespace std;

namespace raytracer
{
	class Scene;
	class Light;
	class DisplayObject;

	class Raytracer
	{
	public:
		static Color		findColor(const Ray &ray, int recursionDepth = 3, float refractInd = 1.0f);

		static Collision	findNearestCollision(const Ray &ray, DisplayObject *&outDObject);
		static Collision	findAnyCollision(const Ray &ray, DisplayObject *&outDObject);

	};
}

