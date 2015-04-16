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
        // TODO: Try to use without init
        ambient = vec3();
        diffuse = vec3();
        emissive = vec3();
        specular = vec3();
        shininess = 1;
    }
}