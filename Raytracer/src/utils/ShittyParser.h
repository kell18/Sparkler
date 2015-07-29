#pragma once
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "../core/Light.h"
#include "../core/Scene.h"
#include "../geometry/Material.h"
#include "../geometry/primitives/Plane.h"
#include "../geometry/primitives/Triangle.h"
#include "../geometry/primitives/Sphere.h"

using namespace std;
using namespace raytracer;
using namespace glm;

class ShittyParser
{

public:
	Camera* camera;
	vector<Light*> lights;
	vector<vec3> vertexBuffer;
	vector<Primitive*> primitives;
	int recursionDepth;
	int width, height;
	Material material;

	Scene*		readfile(const string &filename);
				ShittyParser();
				~ShittyParser();

private: 
	void		rightmultiply(const mat4 & M, stack<mat4> &transform_stack);
	bool		readvals(stringstream &s, const int numvals, float *values);
};

