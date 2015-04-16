#include "Ray.h"

namespace raytracer {

    Ray::Ray(vec3 eye, vec3 direction, float tMin, float tMax)
            : eye(eye), direction(direction), tMin(tMin), tMax(tMax) {
    }

}