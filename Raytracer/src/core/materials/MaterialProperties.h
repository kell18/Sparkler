#pragma once

#include "../../utils/Color.h"

namespace raytracer
{
	struct MaterialProperties
	{
		Color ambient;
		Color diffuse;
		Color specular;
		// Color reflectance;
		Color emissive;
		float shininess;

		// @note: reflectRate + transmitRate <= 1
		float reflectRate;
		float transmitRate;
		float refractInd;

		// TODO: Move somewhere
		float diffuseRad;
		short diffuseSamples;
	};
}