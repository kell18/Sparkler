#include "Ray.h"

namespace raytracer {

    vec4 Ray::trace(const Scene& scene, int depth) {
        auto nearestPrimitives = scene.getNearestPrimitives(this);
        size_t len = nearestPrimitives->size();
        vec4 color;

        auto primitive = nearestPrimitives->begin();
        while (primitive != nearestPrimitives->end()) {
            Collision *collision = (*primitive)->computeCollisionWith(this);
            if (collision->isFind) {
                color.g = 100;
                color.b = 100;
            }
            primitive++;
        }

        return color;
    }

    Ray::Ray(int x, int y, const Camera& camera) : x(x), y(y) {
        float alpha = (float) (tan(camera.getFieldOfView().x/2.0) *
                ((x - camera.width/2.0) / (camera.width/2.0)));
        float beta  = (float) (tan(camera.getFieldOfView().y/2.0) *
                ((camera.height/2.0 - y) / (camera.height/2.0)));

        vec3 camEye = camera.getEye();
        eye = vec4(camEye.x, camEye.y, camEye.z, 1);

        CoordinateSystem cameraFrame = camera.getCoordinateSystem();
        vec3 dir = normalize(alpha * cameraFrame.X + beta * cameraFrame.Y - cameraFrame.Z);
        direction = vec4(dir.x, dir.y, dir.z, 0);
    }
}