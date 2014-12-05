#include "Ray.h"

namespace raytracer {

    vec3 Ray::trace(int depth, vec3 color) {
        if (depth == 0) {
            return color;
        }

        auto nearestCollision = findNearestCollision();
        if (nearestCollision.isFind) {
            color = computeColor(nearestCollision, color); // vec3(200, 200, 200);
        }

        return color;
    }

    // TODO: Optimize: create special method for casting light ray
    Collision Ray::findNearestCollision() const {
        auto nearestPrimitives = scene.getNearestPrimitives(*this);
        auto primitive = nearestPrimitives->begin();

        Collision nearestCollision;
        nearestCollision.distance = tMax + 1.0f;

        while (primitive != nearestPrimitives->end()) {
            Collision collision = (*primitive)->computeCollisionWith(*this);
            if (collision.isFind && collision.distance < nearestCollision.distance) {
                nearestCollision = collision;
            }
            primitive++;
        }
        return nearestCollision;
    }

    vec3 Ray::computeColor(Collision collision, vec3& color) const {
        color += collision.material.ambient + collision.material.emissive;

        auto lightsSrcs = scene.getLights();
        auto lightSrc = lightsSrcs->begin();
        while (lightSrc != lightsSrcs->end()) {
            // TODO: Care with directional light
            Ray lightRay(scene, collision.point, (*lightSrc)->position - collision.point);
            color += (*lightSrc)->computeLight(collision, scene);
            lightSrc++;
        }
        // TODO: createReflectRay and find reflected color recursively

        return color;
    }

    // TODO: May be move functions like this in another entity?
//    Ray Ray::createReflectRay(Ray directRay, Collision collision) {
//        vec3 L = collision.point - directRay.eye;
//        vec3 R = -L + 2 * (dot(L, collision.normal)) * collision.normal;
//        vec3 HalfR = normalize(L + R);
//        return Ray(scene, collision.point, normalize(R));
//
//    }

    Ray::Ray(const Scene& scene, vec3 eye, vec3 direction, float tMin, float tMax)
            : scene(scene), eye(eye), direction(direction), tMin(tMin), tMax(tMax) {
    }
}