#include "Scene.h"

namespace raytracer 
{
	void Scene::render(const char *fileName, int recursionDepth) const
	{
		Film film(camera.width, camera.height);
		Raytracer raytracer(this);
		for (int x = 0, w = camera.width; x < w; ++x) {
			for (int y = 0, h = camera.height; y < h; ++y) {
				Color color = bgColor;
				float shift = 1.f / fragsPerPixel;
				for (int f = 0; f < fragsPerPixel; ++f)
				{
					Ray ray	= camera.rayThroughPixel(x + shift * f, y + shift * f);
					color	+= raytracer.findColor(ray, recursionDepth);
				}
				color /= fragsPerPixel;
				film.commitFragment(x, y, color);
			}
		}
		film.writeToImage(fileName);
	}

	void Scene::addPrimitive(Primitive* primitive) 
	{
		_primitives.push_back(primitive);
	}

	vector<Primitive*> Scene::findNearestPrimitives(const Ray &ray) const
	{
		// TODO: Use tree struct
		return _primitives;
	}

	Scene::Scene(Camera camera, vector<Primitive*> primitives, vector<Light*> lights, 
				 int fragmentsPerPixel, Color bgColor)
		: camera(camera), _primitives(primitives), lights(lights), 
		bgColor(bgColor), fragsPerPixel(fragmentsPerPixel)
	{
		FreeImage_Initialise();
	}

	Scene::~Scene()
	{
		for (auto iterP = _primitives.begin(); iterP != _primitives.end(); iterP++) {
			delete *iterP;
		}
		_primitives.clear();

		for (auto iterL = lights.begin(); iterL != lights.end(); iterL++) {
			delete *iterL;
		}
		lights.clear();

		FreeImage_DeInitialise();
	}
}