#include "Parser.h"

namespace raytracer {

    Scene* Parser::createSceneFromFile(const char *fileName) {
        unsigned width = 640,
                 height = 420;

        Camera *camera = new Camera(width, height, 30);
        camera->lookAt(vec3(0, 0, 8), vec3(1, 0, 0), vec3(0, 1, 0));

        list<Primitive*> *primitives = new list<Primitive*>;
        list<Light*> *lights = new list<Light*>;

        mat4 topTransform;

        Material material1;
        material1.ambient = vec3(1.0f, 1.0f, 1.0f);
        material1.diffuse = vec3(0.8f, 0.1f, 0.0f);
        material1.shininess = 1000;
        material1.specular = vec3(1.0f, 1.0f, 1.0f);

        Material material2;
        material2.ambient = vec3(0.0f, 1.0f, 1.0f);
        material2.diffuse = vec3(1.0f, 1.0f, 0.0f);

        primitives->push_back(new Sphere(vec3(-0.3f, -1.3f, 0.0f), material1, 0.3, topTransform));
        primitives->push_back(new Sphere(vec3(0.7f, -1.3f, 0.0f), material1, 0.3, topTransform));
        primitives->push_back(new Sphere(vec3(1.7f, -1.3f, 0.0f), material1, 0.3, topTransform));
        primitives->push_back(new Sphere(vec3(2.7f, -1.3f, 0.0f), material1, 0.3, topTransform));
        primitives->push_back(new Sphere(vec3(3.7f, -1.3f, 0.0f), material1, 0.3, topTransform));
        primitives->push_back(new Sphere(vec3(0.0f, 1.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(1.0f, 1.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(2.0f, 1.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(3.0f, 1.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(0.0f, 0.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(1.0f, 0.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(2.0f, 0.0f, 0.0f), material2, 0.4, topTransform));
        primitives->push_back(new Sphere(vec3(3.0f, 0.0f, 0.0f), material2, 0.4, topTransform));
//        primitives->push_back(new Sphere(vec3(0.5f, -0.5f, 0.0f), material2, 0.4, topTransform));

        // TODO: Bug on intensity = 1000 || = 2000 etc.
        Light* light1 = new Light(vec3(5.5f, -0.0f, 0.0f), vec4(201.0f, 201.0f, 201.0f, 1.0f), 3500);
        lights->push_back(light1);

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