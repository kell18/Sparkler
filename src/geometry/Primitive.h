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
        vec4 position;
        mat4 transforms;
        Material material;

        virtual Collision*      computeCollisionWith(Ray *ray) = 0;
        // void                 addTransform(mat4 transform);
        // Shape                getShape();

//        Primitive&              operator =(const Primitive &copiedPrimitive);
//                                Primitive();
//                                Primitive(const Primitive &copiedPrimitive);
        virtual                 ~Primitive();
    };

}

#endif