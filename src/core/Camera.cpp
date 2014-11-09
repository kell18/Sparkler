#include "Camera.h"

namespace raytracer {

    Ray* Camera::CreateRay(unsigned xCoord, unsigned yCoord) {
        return new Ray(xCoord, yCoord, this);
    }

    Camera::Camera(const vec3& eye, const vec3& center, const vec3& up,
            unsigned width, unsigned height, int fovx, int fovy) :
                eye(eye), width(width), height(height), fovx(fovx), fovy(fovy) {
        // TODO: May be w = eye - center
        auto eyeVec = eye - center;
        w = normalize(eyeVec);
        u = glm::cross(w, up);
        v = glm::cross(w, u);
    }

}