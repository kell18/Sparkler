#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Material.h"

using namespace glm;

namespace raytracer {

    struct Collision {
        bool isFind;
        vec3 point;
        vec3 normal;
        Material material;
        float distance;

        Collision() : isFind(false), distance(-1) {}
    };

}

#endif