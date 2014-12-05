#include "Light.h"

namespace raytracer {

    vec3 Light::computeLight(const Collision& collision, const Scene& scene) const {
        if (isInShadow(collision, scene)) {
            return vec3(0.0f, 0.0f, 0.0f);
        }
        vec3 L = position - collision.point;
        float LDotN = dot(L, collision.normal);
        vec3 R = -L + (2.0f * LDotN) * collision.normal;
        vec3 halfR = normalize(L + R); // TODO: Try to use half angle
        float distance = length(L);
        float attenuation = computeAttenuation(distance);
        Material material = collision.material;

        float const &d = std::max<float>(LDotN, 0.0f);
        float const &a = dot(R, collision.normal);
        float const &x = std::max<float>(a, 0.0f);
        vec3 result = intensity * attenuation * material.diffuse * d +
                material.specular * pow(x, material.shininess);
        return result;
    }

    float Light::computeAttenuation(float distance) const {
        return 1 / (k_c + k_l * distance + k_q * distance * distance);
    }

    bool Light::isInShadow(const Collision& collision, const Scene& scene) const {
        vec3 collisionPoint = collision.point; //  + (-collision.normal * (float)SHADOW_ACCURANCY); // TODO: Care
        vec3 direction = position - collisionPoint;
        
        Ray lightRay(scene, position, normalize(direction));
        auto nearestCollision = lightRay.findNearestCollision();

        if (nearestCollision.isFind) {
            float distanceToLight = length(direction) - SHADOW_ACCURANCY;
            return nearestCollision.distance < distanceToLight;
        } else {
            return false;
        }
    }

    Light::Light(vec3 position, vec4 color, float intensity, float k_c, float k_l, float k_q) :
            position(position), color(color), intensity(intensity), k_c(k_c), k_l(k_l), k_q(k_q) {
    }
}