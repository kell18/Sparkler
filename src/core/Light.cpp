#include "Light.h"

namespace raytracer {

    bool Light::isVisisbleTo(Ray *ray) {
        // TODO: Realize
        return true;
    }

    Light::Light(vec4 *position, vec4 *color) {
        this->position = position;
        this->color = color;
    }

    Light::Light(float posX, float posY, float posZ, float posW, float colR, float colG, float colB, float colA) {
        this->position = new vec4(posX, posY, posZ, posW);
        this->color = new vec4(colR, colG, colB, colA);
    }

}