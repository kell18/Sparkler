#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include "../geometry/Ray.h"
#include "../geometry/CoordinateSystem.h"

using namespace glm;

namespace raytracer {

    class Ray;

    class Camera {
        CoordinateSystem _coordinateSystem;
        vec3 _eye, _center, _up;
        vec2 _fieldOfView;
        mat4 _modelViewTransform;

    public:
        const unsigned width, height;

        Ray*                        CreateRayTracer(int xCoord, int yCoord) const;

        const mat4&                 lookAt(vec3 eye, vec3 center, vec3 up);


        const CoordinateSystem&     getCoordinateSystem() const;

        const vec3&                 getEye() const;

        const vec3&                 getCenter() const;

        const vec3&                 getUp() const;

        const vec2&                 getFieldOfView() const;
        void                        setFieldOfView(const vec2& fieldOfView);

        const mat4&                 getModelViewTransform() const;


        Camera(unsigned width, unsigned height, float fovxDegree);
    };

}

#endif