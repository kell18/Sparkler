#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "Ray.h"
#include "Collision.h"
#include "../core/Material.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Primitive {
    public:
        vec3 position;
        Material material;
        mat4 transforms;

        virtual Collision       computeCollisionWith(const Ray &ray) = 0;
        // void                 addTransform(mat4 transform);

                                Primitive(vec3 position, Material material, mat4 transforms = mat4());
        virtual                 ~Primitive();
    };

}

#endif