#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

using namespace glm;

namespace raytracer {

    class CoordinateSystem {
    public:
        vec3 X;
        vec3 Y;
        vec3 Z;

        static CoordinateSystem BuildOrthonormalBasis(vec3 _Y, vec3 _Z);
    };

}

#endif