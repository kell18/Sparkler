#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "Scene.h"
#include "../utils/Mathf.h"
#include "../geometry/Ray.h"
#include "../geometry/Collision.h"

#define SHADOW_ACCURANCY 0.00001

using namespace glm;

namespace raytracer {

    class Ray;
    class Scene;

    class Light {
    public:
        float k_c, k_l, k_q; // TODO: Rename
        vec3 position;
        vec4 color;
        float intensity;

        vec3            computeLight(const Collision& collision, const Scene& scene) const;

        float           computeAttenuation(float distance) const;

        bool            isInShadow(const Collision& collision, const Scene& scene) const;

                        Light(vec3 position, vec4 color, float intensity = 100,
                                float k_c = 1, float k_l = 1, float k_q = 1);
    };

}

#endif