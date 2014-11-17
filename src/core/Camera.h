#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../geometry/Ray.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Camera {
    public:
        mat4 modelViewTransform;
        float fovx, fovy;
        unsigned width, height;
        vec3 eye, u, v, w;

        Ray*            CreateRayTracer(int xCoord, int yCoord);
                        Camera(const vec3& eye, const vec3& center, const vec3& up,
                            unsigned width, unsigned height, float fovxDegree, float fovyDegree);
    };

}

#endif