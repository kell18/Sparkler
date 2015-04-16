#include "Parser.h"

namespace raytracer {

    Scene* Parser::createSceneFromFile(const char *fileName) {
        unsigned width = 640,
                 height = 420;

        Camera *camera = new Camera(width, height, 30);
        camera->lookAt(vec3(0, 0, 4), vec3(1, 0, 0), vec3(0, 1, 0));

        list<Primitive*> *primitives = new list<Primitive*>;
        list<Light*> *lights = new list<Light*>;

        mat4 topTransform;

        Material material1;
        material1.ambient = vec3(1.2f, 1.2f, 1.2f);
        material1.emissive = vec3(1.0f, 1.0f, 1.0f);

        material1.diffuse = vec3(5.5f, 0.0f, 0.0f);
        material1.specular = vec3(1.5f, 5.5f, 5.5f);
        material1.shininess = 1;


        Material material2;
        material2.ambient = vec3(0.0f, 0.0f, 0.0f);
        material2.emissive = vec3(0.0f, 0.0f, 0.0f);

        material2.diffuse = vec3(0.9f, 0.9f, 0.0f);
        material2.specular = vec3(0.9f, 0.9f, 0.0f);
        material2.shininess = 1;

        primitives->push_back(new Sphere(vec3(1.0f, -0.0f, -2.0f), material1, 0.5, topTransform));
//        primitives->push_back(new Sphere(vec3(1.0f, 1.0f, 0.0f), material2, 1.0, topTransform));

        lights->push_back(new Light(vec3(2.5f, 3.3f, -1.0f),
                vec3(0.57f, -0.57f, 0.57f), vec4(4.0f, 4.0f, 14.0f, 1.0f), 0.01));

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