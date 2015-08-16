#include <iostream>
#include <vector>
#include <time.h>

#include <FreeImage.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "geometry/primitives/Ray.h"
#include "geometry/primitives/Plane.h"
#include "geometry/primitives/Rectangle.h"
#include "geometry/primitives/Sphere.h"
#include "geometry/primitives/Triangle.h"
#include "core/lights/Light.h"
#include "core/lights/PointLight.h"
#include "core/lights/DirectionalLight.h"
#include "core/Film.h"
#include "core/Camera.h"
#include "core/World.h"
#include "core/Scene.h"
#include "utils/Parser.h"
#include "utils/Direction.h"
#include "utils/Point.h"

using namespace raytracer;
using namespace std;

int main()
{
	string inputFile = "C:\\Dropbox\\Code\\Cpp\\Raytracer\\Raytracer\\res\\test_scenes\\DebugScene.test";
	World::initialize();

	World::setActiveScene(Parser::parseFile(inputFile));
	double renderTime = World::renderActiveScene();

	World::deinitialize();
	cout << "\nRender time: " << renderTime << "ms";
	getchar();
	return 0;
}
