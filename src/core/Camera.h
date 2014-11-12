#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "../geometry/Ray.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Camera {
    public:
        int fovx, fovy;
        unsigned width, height;
        vec3 eye, u, v, w;

        Ray*            CreateRayTracer(unsigned xCoord, unsigned yCoord);
                        Camera(const vec3& eye, const vec3& center, const vec3& up,
                        unsigned width, unsigned height, int fovx, int fovy);
    };

}

#endif