#define GLM_SWIZZLE_XYZW

#include <iostream>
#include "utils/Parser.h"
#include "core/Scene.h"

using namespace std;
using namespace raytracer;

int main() {
    Scene* scene = Parser::createSceneFromFile("scene.xml");

    clock_t start = clock();
    scene->render();
    cout << "\n\nRender time: " << (clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << endl;

    return 0;
}