#pragma once

#include "glm/glm.hpp"
#include "../core/Film.h"

using namespace glm;

namespace raytracer
{
	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		Color emissive;
		float shininess;

		// @note: reflectRate + transmitRate <= 1
		float reflectRate;
		float transmitRate;
		float refractInd;
	};
}
