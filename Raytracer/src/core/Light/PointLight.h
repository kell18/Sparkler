#pragma once

#include "glm/glm.hpp"
#include "Light.h"

using namespace glm;

namespace raytracer 
{

	class PointLight : public Light
	{
		vec3 position;
	public:
		virtual vec3	getDirection(const vec3& point) const;
		virtual float	getDistance(const vec3& point) const;
		virtual vec3	getPosition() const;

						PointLight(vec3 position, Color color, float power = 1.f);
	};

}