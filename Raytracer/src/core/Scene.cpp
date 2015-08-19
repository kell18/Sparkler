#include "Scene.h"

namespace raytracer 
{
	void Scene::render()
	{
		int oneTenth = camera->width / 20;
		cout << "Start rendering.\n";
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
			if (x % oneTenth == 0) {
				string progress = "";
				string equal = "=";
				int tenths = x / oneTenth + 1;
				for (size_t i = 0; i < tenths; i++) {
					progress += equal;
				}
				cout << "Progress: [" << progress << ">" << setw(22 - tenths) << "] "<< tenths*5 <<"%\r";
			}
		}
		cout << "\nDone.";
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