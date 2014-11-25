#include "Camera.h"

namespace raytracer {

    Ray* Camera::CreateRayTracer(int xCoord, int yCoord) const {
        return new Ray(xCoord, yCoord, *this);
    }

    const mat4& Camera::lookAt(vec3 eye, vec3 center, vec3 up) {
        _eye = eye;
        _center = center;
        _up = up;
        _coordinateSystem = CoordinateSystem::BuildOrthonormalBasis(eye - center, up);
        _modelViewTransform = glm::lookAt(eye, center, up);
        return _modelViewTransform;
    }


    const CoordinateSystem& Camera::getCoordinateSystem() const {
        return _coordinateSystem;
    }

    const vec3& Camera::getEye() const {
        return _eye;
    }

    const vec3& Camera::getCenter() const {
        return _center;
    }

    const vec3& Camera::getUp() const {
        return _up;
    }

    const vec2& Camera::getFieldOfView() const {
        return _fieldOfView;
    }

    void Camera::setFieldOfView(const vec2 &fieldOfView) {
        _fieldOfView = fieldOfView;
    }

    const mat4& Camera::getModelViewTransform() const {
        return _modelViewTransform;
    }


    Camera::Camera(unsigned width, unsigned height, float fovxDegree) :
            width(width), height(height) {
        _fieldOfView.x = radians(fovxDegree);
        _fieldOfView.y = radians(fovxDegree*(width/height));
    }

}