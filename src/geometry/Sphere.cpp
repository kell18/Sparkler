#include "Sphere.h"

namespace raytracer {

    Collision* Sphere::computeCollisionWith(Ray *ray) {
        Collision* collision = new Collision();
        float A = dot(ray->direction, ray->direction);
        vec4 EyeMinusPos = ray->eye - (position);
        float B = 2 * (dot(ray->direction, EyeMinusPos));
        float C = dot(EyeMinusPos, EyeMinusPos) - radius * radius;
        float D = B * B - 4 * A * C;
        if (D > 0) {
            collision->isFind = true;
            float sqrtD = sqrtf(D);
            float x1 = (-B + sqrtD) / (2 * A);
            float x2 = (-B - sqrtD) / (2 * A);
            float t;
            if (x1 != x2) {
                t = x1 > x2 ? x1 : x2;
            } else {
                t = x1; // tan(x1);
            }
            collision->point = ray->eye + ray->direction * t;
            collision->normal = vec3(normalize(ray->eye + ray->direction));
        } else {
            collision->isFind = false;
        }

        return collision;
    }

    Sphere::Sphere(vec4 position, float radius, mat4 transforms, Material material) : radius(radius) {
        this->position = position;
        this->transforms = transforms;
        this->material = material;
    }

    Sphere::~Sphere() {
    }

}