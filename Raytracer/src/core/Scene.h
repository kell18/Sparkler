#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <FreeImage.h>

#include "../geometry/primitives/Sphere.h"
#include "DisplayObject.h"
#include "lights/Light.h"
#include "Camera.h"
#include "Film.h"
#include "Raytracer.h"

using namespace std;

namespace raytracer
{
	class Raytracer;
	class Light;
	class DisplayObject;

	class Scene
	{
	private:
		vector<DisplayObject*> dObjects;
		float fragmentShift;
		int fragmentsPerPixel = 2;

	public:
		vector<Light*> lights; // TODO: May be private
		Camera *camera;
		Film *film;
		Color bgColor;
		int recursionDepth = 3;

		void					render();

		vector<DisplayObject*>	findNearestObjects(const Ray &ray) const;
		void					addObject(DisplayObject* object);
		void					addLight(Light* light);
		void					setFragmentsPerPixel(int fragmentsPerPixel);

								Scene(Camera *camera, Film *film, vector<DisplayObject*> objects,
									vector<Light*> lights);
								~Scene();

								Scene(const Scene&) = delete;
								Scene& operator = (const Scene&) = delete;
	};

}