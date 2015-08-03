#pragma once

#include <vector>
#include <cfloat>

#include "glm/glm.hpp"
#include "../geometry/primitives/Primitive.h"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"
#include "Light/Light.h"
#include "Film.h"
#include "Scene.h"

using namespace std;

namespace raytracer
{
	class Scene;
	class Light;

	class Raytracer
	{
	private:
		const Scene *scene;
		const vector<Light*> &lights;

	public:
		Color		findColor(const Ray &ray, int recursionDepth = 3, float indOfRefraction = 1.0f) const;

		Collision	findNearestCollision(const Ray &ray) const;
		Collision	findAnyCollision(const Ray &ray) const;

					Raytracer(const Scene *scene);
					~Raytracer();

					Raytracer(const Raytracer&) = delete;
					Raytracer& operator = (const Raytracer&) = delete;
	};
}

