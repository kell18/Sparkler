#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include "Primitive.h"

using namespace std;

namespace raytracer {

    class Sphere : public Primitive {
    public:
        float radius;

        virtual Collision       computeCollisionWith(const Ray &ray) override;

                                Sphere(vec3 position, Material material, float radius, mat4 transforms = mat4());
        virtual                 ~Sphere();
    };

}

#endif