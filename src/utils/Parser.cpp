#include "Parser.h"

namespace raytracer {

    Scene* Parser::createSceneFromFile(const char *fileName) {
        unsigned width = 500,
                 height = 400;

        Camera *camera = new Camera(
                vec3(-4, -4, 4),
                vec3(1, 0, 0),
                vec3(0, 1, 0),
                width,
                height,
                150, // TODO: Care
                150
        );

        list<Primitive*> *primitives = new list<Primitive*>;
        list<Light*> *lights = new list<Light*>;

        vec4 pos = vec4(1, 0, 0, 1);
        float radius = 2.15;
        mat4 topTransform;
        Material material;

        Primitive *sphere = new Sphere(
                pos,
                radius,
                topTransform,
                material
        );

        primitives->push_back(sphere);

        vec3 vertex1(-1, -1, 0);
        vec3 vertex2(+1, -1, 0);
        vec3 vertex3(+1, +1, 0);

        Primitive *triangle = new Triangle(vertex1, vertex2, vertex3);

//        primitives->push_back(triangle);

        return new Scene(camera, primitives, lights);
        
    }

    bool Parser::readVals(stringstream &s, const int numvals, float* values) {
        for (int i = 0; i < numvals; i++) {
            s >> values[i];
            if (s.fail()) {
                cout << "Failed reading value " << i << " will skip\n";
                return false;
            }
        }
        return true;
    }

}