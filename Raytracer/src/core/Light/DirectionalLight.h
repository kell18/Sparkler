#pragma once 

#include "glm/glm.hpp"
#include "Light.h"

using namespace glm;

namespace raytracer 
{

	class DirectionalLight : public Light
	{
		vec3 direction;
	public:

		virtual float	computeAttenuation(float dist) const;

		virtual vec3	getDirection(const vec3& point) const;
		virtual float	getDistance(const vec3& point) const;

						DirectionalLight(vec3 direction, Color color, float power = 1.f);
						DirectionalLight(vec3 direction, Color color, Attenuation attn, 
							float power = 1.f);
	};

}