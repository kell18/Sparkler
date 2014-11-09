#include "Ray.h"

namespace raytracer {

    vec4 Ray::trace(Scene *scene, int depth) {
        return vec4(0, 199, 123, 1);
    }

    Ray::Ray(unsigned x, unsigned y, Camera* camera) : x(x), y(y), _cam(camera) {
        float alpha = (float) (tan(_cam->fovx/2.0) * ((x - _cam->width/2) / (_cam->width/2)));
        float beta  = (float) (tan(_cam->fovy/2.0) * ((_cam->height/2 - y) / (_cam->height/2)));
        _ray = _cam->eye + normalize(alpha * _cam->u + beta * _cam->v - _cam->w);
    }
}