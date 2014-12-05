#include "Camera.h"

namespace raytracer {

    Ray* Camera::CreateRayTracer(int xCoord, int yCoord, const Scene &scene) const {
        float alpha = _fieldOfView.x *
                ((xCoord - width/2.0f) / (width/2.0f));
        float beta  = tan(_fieldOfView.y/2.0f) *
                ((height/2.0f - yCoord) / (height/2.0f));

        vec3 direction = normalize(alpha * _coordinateSystem.X + beta * _coordinateSystem.Y - _coordinateSystem.Z);

        return new Ray(scene, _eye, direction);
    }

    const mat4& Camera::lookAt(vec3 eye, vec3 center, vec3 up) {
        _eye = eye;
        _center = center;
        _up = up;
        _coordinateSystem = CoordinateSystem::BuildOrthonormalBasis(up, eye - center);
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


    Camera::Camera(unsigned width, unsigned height, float fovyDegree) :
            width(width), height(height) {
        _fieldOfView.y = radians(fovyDegree);
        _fieldOfView.x = tan(_fieldOfView.y / 2.0f) * width / height;
    }

}