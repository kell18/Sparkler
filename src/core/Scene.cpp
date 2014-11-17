#include "Scene.h"

namespace raytracer {

    void Scene::render() {
        Film film(camera->width, camera->height, 24, 1);
        // #pragma omp parallel private(i)
        for (unsigned i = 0; i < camera->width; ++i) {
            for (unsigned j = 0, h = camera->height; j < h; ++j) {
                Ray *rayTracer = camera->CreateRayTracer(i, j);
                film.commitFragment(i, j, rayTracer->trace(this, 2));
            }
        }
        film.writeToImage("../resources/imgs/out.png");
    }

    list<Primitive*>* Scene::getNearestPrimitives(Ray *ray) {
        return _objects;
    }

    void Scene::addPrimitive(Primitive *object) {
        _objects->push_back(object);
    }

    Scene::Scene(Camera *camera, list<Primitive*>* objects, list<Light*> *lights, int fragmentsPerPixel) :
            camera(camera), _objects(objects), lights(lights), fragmentsPerPixel(fragmentsPerPixel) {
    }
}
