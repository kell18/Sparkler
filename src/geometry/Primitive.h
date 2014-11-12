#ifndef Primitive_H
#define Primitive_H

#define GLM_SWIZZLE GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>

//#include <glm/mat4x4.hpp>
//#include <glm/vec4.hpp>
#include "Ray.h"
#include "Collision.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Primitive {
    public:
        vec4 *position;

        virtual Collision*      computeCollisionWith(Ray *ray) = 0;
        // void                 addTransform(mat4 transform);
        // Shape                getShape();
    };
}

#endif