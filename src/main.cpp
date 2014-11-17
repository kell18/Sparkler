#include <iostream>
#include "core/Scene.h"
#include "utils/Parser.h"

using namespace std;
using namespace raytracer;

int main() {
    Scene* scene = Parser::createSceneFromFile("../resources/scenes/scene0.test");

    clock_t start = clock();
    scene->render();
    cout << "\n\nRender time: " << (clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << endl;
//
    return 0;
}