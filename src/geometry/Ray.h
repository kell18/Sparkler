#ifndef RAY_H
#define RAY_H

#define GLM_SWIZZLE_XYZW

#include <math.h>
#include <glm/glm.hpp>
#include "ITracer.h"
#include "../core/Camera.h"

namespace raytracer {

    class Camera;

    class Ray : public ITracer {
    private:
        Camera* _cam;
        
    public:
        vec4 eye, direction;
        int x, y;


        virtual vec4*   trace(Scene* scene, int depth) override;
                        Ray(unsigned x, unsigned y, Camera* camera);
    };

}

#endif