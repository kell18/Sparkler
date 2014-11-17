#include "Material.h"

namespace raytracer {

    Material* Material::clone() const {
        Material* m = new Material;
        m->ambient = ambient;
        m->diffuse = diffuse;
        m->emissive = emissive;
        m->specular = specular;
        m->shininess = shininess;
        return m;
    }

    Material::Material() {
        ambient = vec4();
        diffuse = vec4();
        emissive = vec4();
        specular = vec4();
        shininess = 1;
    }
}