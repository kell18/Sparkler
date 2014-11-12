#include "Sphere.h"

namespace raytracer {

    Collision* Sphere::computeCollisionWith(Ray *ray) {
        Collision* collision = new Collision();
        float A = dot(ray->direction, ray->direction);
        vec4 EyeMinusPos = ray->eye - (*position);
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
                t = tan(x1);
            }
            vec4 wholeRay = ray->eye + ray->direction;
            collision->point = wholeRay * t;
            collision->normal = vec3(normalize(wholeRay));
        } else {
            collision->isFind = false;
        }

        return collision;
    }

    Sphere::Sphere(vec4 *centerPosition, float radius) : radius(radius) {
        position = centerPosition;
    }

}