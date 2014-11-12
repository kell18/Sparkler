#include "Parser.h"

namespace raytracer {

    Scene* Parser::createSceneFromFile(const char *fileName) {
        // TODO: Reuse `readfile` from hw2

        vec3 eye (0.0, 0.0, 0.0),
             center (0.0, 0.0, 1.0),
             up(0.0, 1.0, 0.0);

        Camera* camera = new Camera(eye, center, up, 800, 600, 2, 2);
        auto objects = new vector<Primitive *>();
        return new Scene(camera, objects, 1);
    }

}