#ifndef PARSER_H
#define PARSER_H

#include <glm/vec3.hpp>
#include "../geometry/Primitive.h"
#include "../core/Scene.h"

using namespace glm;

namespace raytracer {

    class Parser {
    public:
        static
        Scene*          createSceneFromFile(const char* fileName);
    };

}

#endif