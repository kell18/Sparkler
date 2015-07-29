#pragma once

#include <limits>
#include <type_traits>

#include "gtest/gtest.h"
#include "glm/glm.hpp"

#include "geometry/primitives/Ray.h"
#include "core/Camera.h"

using namespace std;
using namespace glm;
using namespace raytracer;

class CameraTests : public ::testing::Test
{
protected:
	Camera *camera;

	CameraTests() 
	{
		int width = 640;
		int height = 420;
		camera = new Camera (width, height, 30.0f);
		camera->lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.f, 0.f, 1.f), vec3(0.f, 1.f, 0.f));
	}
	
	virtual ~CameraTests() 
	{
		delete camera;
	}
};

