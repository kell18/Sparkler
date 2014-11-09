#ifndef ITRACER_H
#define ITRACER_H

#include <glm/vec4.hpp>
#include "../core/Scene.h"

using namespace glm;

namespace raytracer {

    class Scene;

    class ITracer {
    public:
        /**
        * Main raytracer method.
        * @param Scene - hold all graphical objects.
        * @param depth - recursion depth.
        * @returns Color in RGBA format.
        */
        virtual vec4        trace(Scene* scene, int depth) = 0;

        virtual             ~ITracer() {}
    };

}

#endif