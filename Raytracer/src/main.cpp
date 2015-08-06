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
	int width = 1240; // 1920;
	int height = 1080; // 1080;
	Camera camera(width, height, 60.0f);
	camera.lookAt(vec3(0.f, -7.f, 7.f), vec3(0.f, 1.f, 0.f), vec3(0.f, 1.f, 1.f)); // -3.f, 2.f
	

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

	Material s1 = { white * 0.0f, white * 0.0f };
	s1.shininess = 100.f;
	s1.reflectRate = 0.01f;
	s1.transmitRate = 0.99f;
	s1.refractInd = 1.1f;
	Material s2 = { emission+0.08f, white*0.4f, emission+0.05f, emission };
	s2.shininess = 150.f;
	s2.reflectRate = 0.0f;
	s2.transmitRate = 0.0f;

	Material pl1 = { ambient, red };
	pl1.shininess = 10.f;
	pl1.reflectRate = 0.f;
	Material pl2 = { ambient + 0.18f };
	pl2.diffuse = Color(0.8f);
	pl2.specular = Color(0.3f);
	pl2.shininess = 200.f;
	pl2.transmitRate = 0.f;
	pl2.reflectRate = 0.f;

	mat4 scaleTransform = scale(vec3(2.5f, 0.55f, 1.f));
	mat4 shiftTransform = translate(vec3(0.f, 0.f, 0.1f));

	Sphere* sp1 = new Sphere(vec3(-1.0f, -1.f, 0.f), 2.0f, s1);
	// sp1->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\earth1.jpg");
	// sp1->transform(rotate(10.f, vec3(0.f, 0.f, 1.f)));
	Sphere* sp2 = new Sphere(vec3(0.5f, 2.5f, -2.5f), 2.0f, s2);
	sp2->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\moon.jpg");

	Rectangle* r1 = new Rectangle(vec3(-18.f, 22.3f, -25.0f), 
		camera.forward * 35.f, camera.right * 30.f * 1.4f, pl2);
	r1->loadTexture("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\Stuff\\TILE_BILAT.jpg");
	

	// cout << r2->normal.x << " " << r2->normal.y << " " << r2->normal.z << endl;

	Triangle* t1 = new Triangle(vec3(-2.f, 0.f, 0.f), vec3(5.f, 0.f, 0.f), 
		vec3(-2.f, 2.f, 5.f), s2);
	t1->transform(translate(vec3(0.f, 1.f, -0.5f)));

	Plane* plane1 = new Plane(vec3(0.f, 0.f, -1.f), vec3(0.f, 0.f, 1.f), pl1);
	plane1->transform(scale(vec3(1.f, 1.f, 2.f))); // ...

	vector<Primitive*> p;
	p.push_back(sp1);
	p.push_back(sp2);
	/*p.push_back(new Sphere(vec3(0.f, .58f, 0.61f), 0.6f, s3, shiftTransform));*/
	/*p.push_back(new Sphere(vec3(-1.5f, 0.8f, 0.85f), 0.6f, s1));*/

	p.push_back(r1);
	
	// p.push_back(t1);

	// p.push_back(plane1);
	/*p.push_back(new Plane(vec3(0.f, 3.f, 0.f), vec3(0.f, -1.f, 0.f), pl2));*/

	vector<Light*> l;
	//l.push_back(new Light(vec3(4.f, -3.f, 5.5f), white, 1.0f, LightType::Point));
	//l.push_back(new DirectionalLight(vec3(-0.3f, 0.3f, -0.3f), white, 1.0f));
	l.push_back(new PointLight(vec3(3.3f, 0.3f, 5.3f), white, 1.5f));
	//l.push_back(new Light(vec3(-1.f, 1.f, 2.f), white, 0.7f));
	//l.push_back(new Light(vec3(0.f, -5.f, 2.f), white, 1.f));

  
	Scene scene(camera, p, l, 2);

	clock_t start = clock();
	scene.render("C:\\Dropbox\\Code\\Cpp\\Raytracer\\Resources\\Imgs\\out.png", 3);
	cout << "\n\nRender time: " << (clock() - start) / (double) (CLOCKS_PER_SEC / 1000) << " ms" << endl;

	getchar();
	return 0;
}
