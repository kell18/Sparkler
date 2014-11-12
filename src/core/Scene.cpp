#include "Scene.h"

namespace raytracer {

    void Scene::render() {
        Film film(_camera->width, _camera->height, 24, 1);
        unsigned i;
        // #pragma omp parallel private(i)
        for (i = 0; i < _camera->width; ++i) {
            for (unsigned j = 0, h = _camera->height; j < h; ++j) {
                Ray *rayTracer = _camera->CreateRayTracer(i, j);
                film.commitFragment(i, j, rayTracer->trace(this, 2));
            }
        }
        film.writeToImage("../resources/out.png");
    }

    vector<Primitive*>* Scene::getNearestPrimitives(Ray *ray) {
        return _objects;
    }

    void Scene::addPrimitive(Primitive *object) {
        _objects->push_back(object);
    }

    Scene::Scene(Camera* _camera, vector<Primitive*>* objects, int fragmentsPerPixel) :
            _camera(_camera), _objects(objects), fragmentsPerPixel(fragmentsPerPixel) {
    }

    Scene::~Scene() {}
}
