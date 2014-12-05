#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

using namespace glm;

namespace raytracer {

    class Material {
    public:
        vec3 ambient;
        vec3 diffuse;
        vec3 emissive;
        vec3 specular;
        float shininess;

        Material*           clone() const;

                            Material();
    };

}

#endif