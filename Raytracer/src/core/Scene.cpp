#include "Scene.h"

namespace raytracer 
{
	void Scene::render()
	{
		for (int x = 0, w = camera->width; x < w; ++x) {
			for (int y = 0, h = camera->height; y < h; ++y) {
				Color color;
				for (int f = 0; f < fragmentsPerPixel; ++f)
				{
					Ray ray	= camera->rayThroughPixel(x + fragmentShift * f, y + fragmentShift * f);
					color  += Raytracer::findColor(ray, recursionDepth);
				}
				color /= fragmentsPerPixel;
				film->commitFragment(x, y, color);
			}
		}
		film->pushFragments();
	}

	vector<DisplayObject*> Scene::findNearestObjects(const Ray &ray) const
	{
		// TODO: Use accel tree struct
		return dObjects;
	}

	void Scene::addObject(DisplayObject* dObject)
	{
		dObjects.push_back(dObject);
	}

	void Scene::addLight(Light* light) 
	{
		lights.push_back(light);
	}

	void Scene::setFragmentsPerPixel(int fragmentsPerPixel)
	{
		this->fragmentsPerPixel = fragmentsPerPixel;
		fragmentShift = 1.0f / fragmentsPerPixel;
	}

	Scene::Scene(Camera *camera, Film *film, vector<DisplayObject*> dObjects,  vector<Light*> lights)
		: camera(camera), film(film), dObjects(dObjects), lights(lights)
	{
		fragmentShift = 1.0f / fragmentsPerPixel;
	}

	Scene::~Scene()
	{
		for (auto iterP = dObjects.begin(); iterP != dObjects.end(); iterP++) {
			delete *iterP;
		}
		dObjects.clear();

		for (auto iterL = lights.begin(); iterL != lights.end(); iterL++) {
			delete *iterL;
		}
		lights.clear();

		delete camera;
		delete film;
	}
}