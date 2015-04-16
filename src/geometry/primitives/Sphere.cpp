#include "Sphere.h"

namespace raytracer {

    Collision Sphere::computeCollisionWith(Ray const &ray) {
        Collision collision;

        float A = dot(ray.direction, ray.direction);
        vec3 EyeMinusPos = ray.eye - (position);
        float B = 2 * (dot(ray.direction, EyeMinusPos));
        float C = dot(EyeMinusPos, EyeMinusPos) - radius * radius;
        float D = B * B - 4 * A * C;

        if (D > 0) {
            float sqrtD = sqrtf(D);
            float x1 = (-B + sqrtD) / (2 * A);
            float x2 = (-B - sqrtD) / (2 * A);
            float t;
            if (x1 != x2) {
                t = x1 > x2 ? x1 : x2;
            } else {
                t = x1; // tan(x1);
            }
            if (t < ray.tMax && t > ray.tMin) {
                collision.isFind = true;
                collision.point = ray.eye + ray.direction * t;
                collision.normal = normalize(ray.eye + ray.direction);
                collision.distance = length(collision.point - ray.eye);
                collision.material = material;
            }
        }

        return collision;
    }

    Sphere::Sphere(vec3 position, Material material, float radius, mat4 transforms)
            : Primitive(position, material, transforms), radius(radius) {
    }

    Sphere::~Sphere() {
    }

}