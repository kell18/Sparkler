#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

using namespace glm;

namespace raytracer {

    class Ray {
    public:
        vec3 eye, direction;
        float tMin;
        float tMax;

                        Ray(vec3 eye, vec3 direction, float tMin = 0.1f, float tMax = 1000.0f);
    };

}

#endif