#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <FreeImage.h>

#include "../geometry/primitives/Primitive.h"
#include "../geometry/primitives/Sphere.h"
#include "Light/Light.h"
#include "Camera.h"
#include "Film.h"
#include "Raytracer.h"

using namespace std;

namespace raytracer
{
	class Raytracer;
	class Light;

	class Scene
	{
	private:
		vector<Primitive*> _primitives;
		float fragmentShift = 0.5f;
		int fragmentsPerPixel = 2;

	public:
		vector<Light*> lights;
		Camera *camera;
		Film *film;
		Color bgColor;
		int recursionDepth = 3;

		void				render();

		vector<Primitive*>	findNearestPrimitives(const Ray &ray) const;
		void				addPrimitive(Primitive* primitive);

		void				addLight(Light* light);

		void				setFragmentsPerPixel(int fragmentsPerPixel);

							Scene(Camera *camera, Film *film, vector<Primitive*> primitives, 
								vector<Light*> lights);
							~Scene();

							Scene(const Scene&) = delete;
							Scene& operator = (const Scene&) = delete;
	};

}