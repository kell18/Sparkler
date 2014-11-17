#ifndef LIGHT_H
#define LIGHT_H

#include "glm/vec4.hpp"
#include "../geometry/Ray.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Light {
    public:
        vec4 *position;
        vec4 *color;

        bool            isVisisbleTo(Ray *ray);
                        Light(vec4 *position, vec4 *color);
                        Light(float posX, float posY, float posZ, float posW,
                                float colR, float colG, float colB, float colA);
    };

}

#endif