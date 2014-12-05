#include "Scene.h"

namespace raytracer {

    void Scene::render() {
        Film film(camera->width, camera->height, 24, 1);
        // #pragma omp parallel for
        for (unsigned i = 0; i < camera->width; ++i) {
            for (unsigned j = 0, h = camera->height; j < h; ++j) {
                Ray* ray = camera->CreateRayTracer(i, j, *this);
                vec3 color = ray->trace(2);
                film.commitFragment(i, j, vec4(color, 1));
                delete ray;
            }
        }
        film.writeToImage("../resources/imgs/out.png");
    }

    list<Primitive*>* Scene::getNearestPrimitives(const Ray &ray) const {
        return _primitives;
    }

    void Scene::addPrimitive(Primitive *primitive) {
        _primitives->push_back(primitive);
    }

    list<Light *> *Scene::getLights() const {
        return _lights;
    }

    void Scene::addLight(Light *light) {
        _lights->push_back(light);
    }

    Scene::Scene(Camera *camera, list<Primitive*>* objects, list<Light*> *lights, int fragmentsPerPixel) :
            camera(camera), _primitives(objects), _lights(lights), fragmentsPerPixel(fragmentsPerPixel) {
    }

    Scene::~Scene() {
        for(auto iterP = _primitives->begin(); iterP != _primitives->end(); iterP++) {
            delete *iterP;
        }
        _primitives->clear();
        delete _primitives;

        for(auto iterL = _lights->begin(); iterL != _lights->end(); iterL++) {
            delete *iterL;
        }
        _lights->clear();
        delete _lights;

        delete camera;
    }
}
