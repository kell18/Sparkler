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
#include "core/World.h"
#include "core/Scene.h"
#include "utils/Parser.h"
#include "utils/Direction.h"
#include "utils/Point.h"

using namespace raytracer;
using namespace std;


int main() 
{
	int width = 1240; // 1920;
	int height = 1080; // 1080;
	Camera *camera = new Camera(width, height, 60.0f);
	camera->lookAt(vec3(0.f, -7.f, 7.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 1.f)); // -3.f, 2.f

	string outputFile = "C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\out.png";
	Film *film = new Film(width, height, outputFile);	

	Color ambient(.0f, .0f, .0f);
	Color diffuse(0.f, 0.05f, 0.05f);
	Color specular(.7f, .7f, .7f);
	Color emission(.0f, .0f, 0.f);

	Color blue(0.f, 0.3f, 0.3f);
	Color yellow(0.3f, 0.3f, 0.f);
	Color gray(0.3f, 0.3f, 0.3f);
	Color red(0.8f, 0.2f, 0.2f);
	Color green(0.2f, 0.8f, 0.2f);
	Color white(1.f, 1.f, 1.f);

	Material metal;
	metal.diffuse = Color(0.005f);
	metal.specular = specular + 0.28f;
	metal.ambient = ambient;
	metal.shininess = 400.f;
	metal.reflectRate = 1.0f;

	Material plastic;
	plastic.diffuse = Color(0.7f, 0.7f, 0.1f);
	plastic.specular = Color(0.5f, 0.5f, 0.05f);
	plastic.ambient = ambient;
	plastic.shininess = 100.f;
	plastic.reflectRate = 0.3f;
	plastic.transmitRate = 0.0f;

	Material s1 = { white * 0.0f, white * 0.0f, white * 0.99f };
	s1.shininess = 200.f;
	s1.reflectRate = 0.05f;
	s1.transmitRate = 0.95f;
	s1.refractInd = 1.1f;

	Material pl2 = { ambient + 0.18f };
	pl2.diffuse = Color(0.8f);
	pl2.specular = Color(0.3f);
	pl2.shininess = 200.f;
	pl2.transmitRate = 0.f;
	pl2.reflectRate = 0.f;

	mat4 scaleTransform = scale(vec3(2.5f, 0.55f, 1.f));
	mat4 shiftTransform = translate(vec3(0.f, 0.f, 0.1f));

	Sphere* sp1 = new Sphere(vec3(0.0f, -1.0f, 0.0f), 2.0f, s1);
	// sp1->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\earth1.jpg");
	// sp1->transform(rotate(10.f, vec3(0.f, 0.f, 1.f)));
	Sphere* sp2 = new Sphere(vec3(-2.0f, 5.0f, -4.0f), 3.0f, plastic);
	// sp2->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\moon.jpg");

	Rectangle* r1 = new Rectangle(vec3(-18.f, 22.3f, -25.0f), 
		camera->forward * 35.f, camera->right * 30.f * 1.4f, pl2);
	r1->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\GreenAndYellow.jpg");

	vector<Primitive*> p;
	p.push_back(sp1);
	p.push_back(sp2);

	p.push_back(r1);

	vector<Light*> l;
	// l.push_back(new DirectionalLight(vec3(0.3f, -0.3f, -0.3f), white, 1.0f));
	l.push_back(new PointLight(vec3(3.3f, 0.3f, 5.3f), white, 1.5f));

  
	World::setActiveScene(new Scene(camera, film, p, l));
	World::getActiveScene()->setFragmentsPerPixel(2);

	clock_t start = clock();
	World::renderActiveScene();
	cout << "\n\nRender time: " << (clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << endl;

	getchar();
	return 0;
}
