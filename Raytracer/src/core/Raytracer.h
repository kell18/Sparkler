#pragma once

#include <vector>
#include <cfloat>

#include "../utils/Mathf.h"
#include "../geometry/primitives/Primitive.h"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"
#include "../utils/Mathf.h"
#include "Light/Light.h"
#include "Film.h"
#include "Scene.h"
#include "World.h"

using namespace std;

namespace raytracer
{
	class Scene;
	class Light;

	class Raytracer
	{
	public:
		static Color		findColor(const Ray &ray, int recursionDepth = 3, float refractInd = 1.0f);

		static Collision	findNearestCollision(const Ray &ray);
		static Collision	findAnyCollision(const Ray &ray);

	};
}

