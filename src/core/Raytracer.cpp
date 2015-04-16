#include "Raytracer.h"

namespace raytracer {

    vec3 Raytracer::trace(const Ray &ray, unsigned recursionDepth, vec3 startColor) const {
        if (recursionDepth < 1) {
            return startColor;
        }
        auto collision = findNearestCollisionTo(ray);
        if (collision.isFind) {
            const Material& material = collision.material;
            startColor += material.ambient + material.emissive;

            auto lightsSrcs = _scene.getLights();
            auto lightSrc = lightsSrcs->begin();
            while (lightSrc != lightsSrcs->end()) {
                startColor += computeLighting((*(*lightSrc)), collision, ray);
                lightSrc++;
            }

            Ray reflectedRay = createReflectedRay(ray, collision);
            startColor += material.specular * trace(reflectedRay, recursionDepth - 1, startColor);
        }

        return startColor;
    }

    Collision Raytracer::findNearestCollisionTo(const Ray &ray) const {
        auto nearestPrimitives = _scene.getNearestPrimitivesTo(ray);
        auto primitive = nearestPrimitives->begin();

        Collision nearestCollision;
        nearestCollision.distance = ray.tMax + 1.0f;

        while (primitive != nearestPrimitives->end()) {
            Collision collision = (*primitive)->computeCollisionWith(ray);
            if (collision.isFind && collision.distance < nearestCollision.distance) {
                nearestCollision = collision;
            }
            primitive++;
        }
        return nearestCollision;
    }

    Ray Raytracer::createReflectedRay(const Ray &directRay, const Collision &collision) const {
//        vec3 L = collision.point - directRay.eye;
        vec3 R = directRay.direction - 2 * (dot(directRay.direction, collision.normal)) * collision.normal;
//        vec3 HalfR = normalize(L + R);
        return Ray(collision.point, R);
    }

    vec3 Raytracer::computeLighting(const Light &light, const Collision &collision, const Ray &ray) const {
        //        if (isInShadow(collision, scene)) {
//            return vec3(0.0f, 0.0f, 0.0f);
//        }
        Material material = collision.material;

        vec3 lightDirection = normalize(light.direction); // normalize(position - collision.point);
        float nDotL = std::max(dot(collision.normal, lightDirection), 0.0f);
        vec3 diffuse = material.diffuse * vec3(light.color) * nDotL;

        vec3 halfVec = normalize(lightDirection + normalize(-ray.direction));
        float nDotH = std::max(dot(collision.normal, halfVec), 0.0f);
        vec3 specular = material.specular * vec3(light.color) * std::pow(nDotH, material.shininess);

        vec3 result = diffuse + specular;

        return result;
    }

    bool Raytracer::isInShadow(const Light& light, Collision const &collision) const {
        vec3 collisionPoint = collision.point;
        vec3 direction = collisionPoint - light.position;

        Ray lightRay(light.position, normalize(direction));
        auto nearestCollision = findNearestCollisionTo(lightRay);

        if (nearestCollision.isFind) {
            float distanceToLight = length(direction) - SHADOW_ACCURACY;
            return nearestCollision.distance < distanceToLight;
        } else {
            return false;
        }
    }

    Raytracer::Raytracer(const Scene &scene) : _scene(scene) {
    }
}