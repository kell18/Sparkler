#include <iostream>
#include "utils/Parser.h"
#include "core/Scene.h"

using namespace std;
using namespace raytracer;

int main() {
    Scene* scene = Parser::createSceneFromFile("scene.xml");
    scene->render();
    return 0;
}