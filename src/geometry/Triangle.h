#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "Primitive.h"
#include "Collision.h"

namespace raytracer {

    class Triangle : public Primitive {
    private:
        vec3 vertex1, vertex2, vertex3,
             vec1x2, vec1x3, normal;


    public:
        virtual             Collision *computeCollisionWith(Ray *ray) override;

                            Triangle(vec3 vertex1, vec3 vertex2, vec3 vertex3);
        virtual             ~Triangle();
    };

}

#endif