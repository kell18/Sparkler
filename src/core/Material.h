#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec4.hpp>

using namespace glm;

namespace raytracer {

    class Material {
    public:
        vec4 ambient;
        vec4 diffuse;
        vec4 emissive;
        vec4 specular;
        float shininess;

        Material*           clone() const;

                            Material();
    };

}

#endif