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
		virtual Color		computeShadeColor(const Direction &eyeDir, const Collision &c, 
								const MaterialProperties &materialProps) const override;

		virtual Direction	getDirection(const Position& point) const override;
		virtual float		getDistance(const Position& point) const override;
		virtual Position	getPosition() const override;

							AreaLight(Color color, Rectangle *rect, int samples = 4, 
								float power = 1.0f);
	protected:
		Color				computeFragmentShade(const Direction &eyeDir, const Collision &c,
								const MaterialProperties &materialProps, 
								const Direction &lrayVect) const;
	};
}