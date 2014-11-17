#include "Triangle.h"

#define EPSILON 0.0001

namespace raytracer {

    Collision *Triangle::computeCollisionWith(Ray *ray) {
        Collision *collision = new Collision;

        vec4 homogenNormal = vec4(normal, 0);
        float denominator = dot(ray->direction, homogenNormal);

        if (!(denominator < EPSILON && denominator > -EPSILON))  {
            collision->isFind = true;
            float t = (dot(vec1x2, normal) - dot(ray->eye, homogenNormal)) / denominator;
            collision->point = (ray->eye + ray->direction) * t;
            collision->normal = normal;
        } else {
            collision->isFind = false;
        }

        return collision;
    }

    Triangle::Triangle(vec3 vertex1, vec3 vertex2, vec3 vertex3) :
            vertex1(vertex1), vertex2(vertex2), vertex3(vertex3) {
        vec1x2 = vertex2 - vertex1;
        vec1x3 = vertex3 - vertex1;
        normal = cross(vec1x2, vec1x3);
    }

    Triangle::~Triangle() {
    }
}