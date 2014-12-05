#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include <glm/vec3.hpp>
#include <omp.h>
#include <iostream>
#include <list>
#include "../geometry/Primitive.h"
#include "../geometry/Ray.h"
#include "Camera.h"
#include "Film.h"
#include "Light.h"

using namespace std;
using namespace glm;

namespace raytracer {

    class Camera;
    class Ray;
    class Primitive;
    class Light;

    class Scene{
    private:
        int fragmentsPerPixel;
        list<Primitive*> *_primitives;
        list<Light*>* _lights;

    public:
        Camera *camera;

        void                    render();

        list<Primitive*>*       getNearestPrimitives(const Ray &ray) const;
        void                    addPrimitive(Primitive *primitive);

        list<Light*>*           getLights() const;
        void                    addLight(Light* light);


                                Scene(Camera* camera, list<Primitive*>* objects,
                                        list<Light*> *lights, int fragmentsPerPixel = 1);
                                ~Scene();
    };

}

#endif