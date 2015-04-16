#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "../core/Scene.h"
#include "../utils/Mathf.h"
#include "primitives/Ray.h"
#include "Collision.h"

#define SHADOW_ACCURANCY 0.0001

typedef unsigned char BYTE;

using namespace glm;

namespace raytracer {

    class Ray;
    class Scene;

    class Light {
    public:
        float k_c, k_l, k_q; // TODO: Rename
        vec3 position, direction;
        vec4 color;
        float intensity;

        float           computeAttenuation(float distance) const;

                        Light(vec3 position, vec3 direction, vec4 color, float intensity = 200,
                                float k_c = 1, float k_l = 1, float k_q = 1);
    };

}



#endif