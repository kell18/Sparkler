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

    public:
        Camera *camera;
        list<Light*> *lights;

        void                    render();

        list<Primitive*>*       getNearestPrimitives(Ray *ray) const;
        void                    addPrimitive(Primitive *primitive);


                                Scene(Camera* camera, list<Primitive*>* objects,
                                        list<Light*> *lights, int fragmentsPerPixel = 1);
                                ~Scene();
    };

}

#endif