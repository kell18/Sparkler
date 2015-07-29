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
		bool isMirroring;
	};
}
