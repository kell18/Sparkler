#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>
#include "Primitive.h"

namespace raytracer {

    class Sphere : public Primitive {

    public:
        float radius;

        virtual Collision*      computeCollisionWith(Ray *ray) override;
                                Sphere(vec4* centerPosition, float radius);
    };

}

#endif