#include <iostream>
#include <vector>
#include <time.h>

#include <FreeImage.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "geometry/primitives/Ray.h"
#include "geometry/primitives/Primitive.h"
#include "geometry/primitives/Plane.h"
#include "geometry/primitives/Rectangle.h"
#include "geometry/primitives/Sphere.h"
#include "geometry/primitives/Triangle.h"
#include "geometry/Material.h"
#include "core/Light/Light.h"
#include "core/Light/PointLight.h"
#include "core/Light/DirectionalLight.h"
#include "core/Film.h"
#include "core/Camera.h"
#include "core/Scene.h"
#include "utils/ShittyParser.h"
#include "utils/Direction.h"
#include "utils/Point.h"

using namespace raytracer;
using namespace std;


int main() 
{
	ShittyParser sp;
	Scene *scene = sp.readfile("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Testscenes\\hw3-submissionscenes\\scene4-specular.test");

	clock_t start = clock();
	scene->render("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\out.png", 3);
	cout << "\n\nRender time: " << (clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << endl;

	getchar();
	return 0;
}
