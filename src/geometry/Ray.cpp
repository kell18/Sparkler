#include "Ray.h"

namespace raytracer {

    vec4* Ray::trace(Scene *scene, int depth) {
//        auto nearestObjects = scene->getNearestPrimitives(this);
        return new vec4(255, 250, 250, 1);
    }

    Ray::Ray(unsigned x, unsigned y, Camera* camera) : x(x), y(y), _cam(camera) {
        float alpha = (float) (tan(_cam->fovx/2.0) * ((x - _cam->width/2) / (_cam->width/2)));
        float beta  = (float) (tan(_cam->fovy/2.0) * ((_cam->height/2 - y) / (_cam->height/2)));
        vec3& camEye = _cam->eye;
        eye = vec4(camEye.x, camEye.y, camEye.z, 1);
        vec3 dir = normalize(alpha * _cam->u + beta * _cam->v - _cam->w);
        direction = vec4(dir.x, dir.y, dir.z, 0);
    }
}