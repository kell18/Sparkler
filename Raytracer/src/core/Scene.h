#pragma once

#include <vector>
#include <iostream>

#include "FreeImage.h"
#include "../geometry/primitives/Primitive.h"
#include "Light.h"
#include "Camera.h"
#include "Film.h"
#include "Raytracer.h"

using namespace std;

namespace raytracer
{
	class Raytracer;

	class Scene
	{
	private:
		vector<Primitive*> _primitives;
	public:
		vector<Light*> lights;
		Camera camera;
		Color bgColor;
		int fragsPerPixel;

		void				render(const char* fileName, int recursionDepth = 3) const;

		vector<Primitive*>	findNearestPrimitives(const Ray &ray) const;
		void				addPrimitive(Primitive* primitive);

							Scene(Camera camera, vector<Primitive*> primitives, vector<Light*> lights,
								  int fragmentsPerPixel = 2, Color bgColor = Color());
							~Scene();

							Scene(const Scene&) = delete;
							Scene& operator = (const Scene&) = delete;
	};

}