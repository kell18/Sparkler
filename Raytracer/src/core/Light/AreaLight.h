#pragma once

#include "Light.h"
#include "../../utils/Mathf.h"
#include "../../geometry/primitives/Rectangle.h"

namespace raytracer 
{
	class AreaLight : public Light
	{
		Rectangle* rect;
		int samples;
		float samplesSqr;
		float shift;
		float distance;
	public:
		virtual Color		computeShadeColor(const Direction &eyeDir, const Collision &c) const;

		virtual Direction	getDirection(const Position& point) const;
		virtual float		getDistance(const Position& point) const;
		virtual Position	getPosition() const;

							AreaLight(Color color, Rectangle *rect, int samples = 4, 
								float power = 1.0f);
	protected:
		Color				computeFragmentShade(const Direction &eyeDir, const Collision &c,
								const Direction &lrayVect) const;
	};
}