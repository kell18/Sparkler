#include "Primitive.h"

namespace raytracer {

    Primitive::Primitive(vec3 position, Material material, mat4 transforms)
                    : position(position), material(material), transforms(transforms) {
    }

    Primitive::~Primitive() {
    }

}