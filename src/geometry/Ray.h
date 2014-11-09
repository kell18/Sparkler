#ifndef RAY_H
#define RAY_H

#include <math.h>
#include "ITracer.h"
#include "../core/Camera.h"

namespace raytracer {

    class Camera;

    class Ray : public ITracer {
    private:
        vec3 _ray;
        Camera* _cam;
    public:
        int x, y;


        virtual vec4        trace(Scene* scene, int depth) override;

                            Ray(unsigned x, unsigned y, Camera* camera);
    };

}

#endif