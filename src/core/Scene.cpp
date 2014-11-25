#include "Scene.h"

namespace raytracer {

    void Scene::render() {
        Film film(camera->width, camera->height, 24, 1);
        // #pragma omp parallel for
        for (unsigned i = 0; i < camera->width; ++i) {
            for (unsigned j = 0, h = camera->height; j < h; ++j) {
                Ray* ray = camera->CreateRayTracer(i, j);
                vec4 color = ray->trace(*this, 2);
                film.commitFragment(i, j, color);
                delete ray;
            }
        }
        film.writeToImage("../resources/imgs/out.png");
    }

    list<Primitive*>* Scene::getNearestPrimitives(Ray *ray) const {
        return _primitives;
    }

    void Scene::addPrimitive(Primitive *primitive) {
        _primitives->push_back(primitive);
    }

    Scene::Scene(Camera *camera, list<Primitive*>* objects, list<Light*> *lights, int fragmentsPerPixel) :
            camera(camera), _primitives(objects), lights(lights), fragmentsPerPixel(fragmentsPerPixel) {
    }

    Scene::~Scene() {
        for(auto iterP = _primitives->begin(); iterP != _primitives->end(); iterP++) {
            delete *iterP;
        }
        _primitives->clear();
        delete _primitives;

        for(auto iterL = lights->begin(); iterL != lights->end(); iterL++) {
            delete *iterL;
        }
        lights->clear();
        delete lights;

        delete camera;
    }
}
