#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <glm/vec4.hpp>
#include "../core/Camera.h"
#include "../core/Scene.h"
#include "../geometry/CoordinateSystem.h"
#include "../geometry/Collision.h"

namespace raytracer {

    class Camera;
    class Scene;

    class Ray {
    public:
        const Scene& scene;
        vec3 eye, direction;
        float tMin;
        float tMax;

        vec3            trace(int depth, vec3 color = vec3());
        Collision       findNearestCollision() const;

        vec3            computeColor(Collision collision, vec3& color) const;

//        static Ray      createReflectRay(Ray directRay, Collision collision);

                        Ray(const Scene& scene, vec3 eye, vec3 direction, float tMin = 0.1f, float tMax = 1000.0f);
    };

}

#endif