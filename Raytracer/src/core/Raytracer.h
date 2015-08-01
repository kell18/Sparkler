#pragma once

#include <vector>
#include <cfloat>

#include "glm/glm.hpp"
#include "../geometry/primitives/Primitive.h"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"
#include "Light.h"
#include "Film.h"
#include "Scene.h"

using namespace std;

namespace raytracer
{
	class Scene;

	class Raytracer
	{
	private:
		const Scene *scene;
		const vector<Light*> &lights;

	public:
		Color		trace(const Ray &ray, int recursionDepth = 3, float indOfRefraction = 1.0f) const;
		Collision	cast(const Ray &ray) const;

		bool		isInShadow(vec3 point, vec3 toLightDir, float distToLight) const;
		float		countAmountOfLight(vec3 point, vec3 toLightDir, float distToLight) const;

					Raytracer(const Scene *scene);
					~Raytracer();

					Raytracer(const Raytracer&) = delete;
					Raytracer& operator = (const Raytracer&) = delete;
	};
}

