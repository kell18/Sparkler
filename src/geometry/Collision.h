#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

namespace raytracer {

    struct Collision {
        bool isFind;
        vec4 point;
        vec3 normal;
    };

}

#endif