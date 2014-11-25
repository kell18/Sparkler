#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <glm/vec4.hpp>
#include "../core/Camera.h"
#include "../core/Scene.h"
#include "../geometry/CoordinateSystem.h"

namespace raytracer {

    class Camera;
    class Scene;

    class Ray {
    public:
        vec4 eye, direction;
        int x, y;

        vec4            trace(const Scene& scene, int depth) ;

                        Ray(int x, int y, const Camera& camera);
    };

}

#endif