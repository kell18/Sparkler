#pragma once

#include "glm/glm.hpp"
#include "Film.h"

using namespace glm;

namespace raytracer
{
	enum LightType { Point, Directional };

	// TODO: make this point l. and make abstract base class
	class Light
	{
	private:
		float _constAttenCoef;
		float _linearAttenCoef;
		float _quadAttenCoef;
	public:
		LightType type;
		vec3 posOrDir;
		Color color;
		float power, fallof, deadDist;

		// TODO: Move in base class
		float	computeAttenuation(float dist) const;
		vec3	getDirection(const vec3& point) const;
		float	getDistance(const vec3& point) const;

				Light(vec3 posOrDir, Color color, float power, LightType type = Point);
	};
}

