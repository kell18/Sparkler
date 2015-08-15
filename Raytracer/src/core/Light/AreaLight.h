#pragma once

#include <glm/glm.hpp>
#include "Light.h"
#include "../../geometry/primitives/Rectangle.h"
#include "../../utils/Mathf.h"

using namespace glm;

namespace raytracer 
{
	class AreaLight : public Light
	{
		vec3 direction;
		Rectangle* rect;
		int samples;
		float samplesSqr;
		float shift;
		float distance;
	public:
		virtual Color	computeShadeColor(const vec3 &eyeDir, const Collision &c) const;

		virtual vec3	getDirection(const vec3& point) const;
		virtual float	getDistance(const vec3& point) const;
		virtual vec3	getPosition() const;

						AreaLight(Color color, Rectangle *rect, int samples = 4, float power = 1.0f);
	protected:
		Color			computeFragmentShade(const vec3 &eyeDir, const Collision &c, const vec3 &lrayVect) const;
	};
}