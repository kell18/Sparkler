#include "Light.h"

namespace raytracer {

    float Light::computeAttenuation(float distance) const {
        return 1 / (k_c + k_l * distance + k_q * distance * distance);
    }

    Light::Light(vec3 position, vec3 direction, vec4 color, float intensity, float k_c, float k_l, float k_q) :
            position(position), direction(direction), color(color), intensity(intensity), k_c(k_c), k_l(k_l), k_q(k_q) {
    }
}
