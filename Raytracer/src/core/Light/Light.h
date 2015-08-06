#pragma once

#include <glm/glm.hpp>

#include "../Color.h"
#include "../../geometry/Collision.h"
#include "../Film.h"
#include "../Raytracer.h"
#include "../../geometry/primitives/Ray.h"

using namespace glm;

namespace raytracer
{
	class Raytracer;

	class Light
	{
	protected:
		float _constAttenCoef;
		float _linearAttenCoef;
		float _quadAttenCoef;
	public:
		Color color;
		float power;

		virtual Color	computeShadeColor(vec3 eyeDir, const Collision &c, const Raytracer* tracer) const;
		virtual float	computeAttenuation(float dist) const;

		virtual vec3	getDirection(const vec3& point) const = 0;
		virtual float	getDistance(const vec3& point) const = 0;

						Light(Color color, float power);
		virtual			~Light();
	};
}

