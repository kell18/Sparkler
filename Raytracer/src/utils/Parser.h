#pragma once
 
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "../core/Light/PointLight.h"
#include "../core/Light/DirectionalLight.h"
#include "../core/Light/AreaLight.h"
#include "../core/Scene.h"
#include "../geometry/Material.h"
#include "../geometry/primitives/Plane.h"
#include "../geometry/primitives/Rectangle.h"
#include "../geometry/primitives/Triangle.h"
#include "../geometry/primitives/Sphere.h"
#include "SceneBuilder.h"

using namespace std;
using namespace glm;

namespace raytracer {

	class Parser
	{

	public:
		static Scene*	parseFile(const string &filename);

	private: 
		static bool		readVals(stringstream &s, const int numvals, float *values);
	};

}