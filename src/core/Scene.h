#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include <glm/vec3.hpp>
#include <omp.h>
#include "../geometry/Primitive.h"
#include "../geometry/Ray.h"
#include "Camera.h"
#include "Film.h"

using namespace std;
using namespace glm;

namespace raytracer {

    class Camera;
    class Ray;
    class Primitive;

    class Scene{
    private:
        int fragmentsPerPixel;
        Camera* _camera;
        vector<Primitive*> *_objects;

    public:
        void                    render();
        vector<Primitive*>*     getNearestPrimitives(Ray *ray);
        void                    addPrimitive(Primitive *object);
                                Scene(Camera* camera, vector<Primitive*>* objects, int fragmentsPerPixel);
                                ~Scene();
    };

}

#endif