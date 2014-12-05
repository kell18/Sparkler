#ifndef TRIANGLE_H
#define TRIANGLE_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/epsilon.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Primitive.h"
#include "Collision.h"

using namespace glm;

namespace raytracer {

    class Triangle : public Primitive {
    private:
        vec3 vertices[3];
        vec3 side1x2, side1x3, normal;


    public:
        virtual Collision       computeCollisionWith(const Ray &ray) override;


                                Triangle(Material material, vec3 vertices[3], mat4 transforms = mat4());

        virtual                 ~Triangle();

    };

}

#endif