#include "Camera.h"

namespace raytracer {

    Ray* Camera::CreateRayTracer(int xCoord, int yCoord) {
        return new Ray(xCoord, yCoord, this);
    }

    Camera::Camera(const vec3& eye, const vec3& center, const vec3& up,
            unsigned width, unsigned height, float fovxDegree, float fovyDegree) :
                eye(eye), width(width), height(height), fovx(radians(fovxDegree)), fovy(radians(fovyDegree)) {
        // TODO: May be w = eye - center
        auto eyeVec = eye - center;
        w = normalize(eyeVec);
        u = glm::cross(up, w);
        v = glm::cross(w, u);
        modelViewTransform = glm::lookAt(eye, center, up);
    }

}