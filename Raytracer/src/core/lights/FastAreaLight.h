#pragma once

#include "Light.h"

namespace raytracer 
{
	class FastAreaLight : public Light
	{
	private:
		Position position;
	public:
		virtual Color		computeShadeColor(const Collision &c,
								const MaterialProperties &mProperties) const override;

		virtual Direction	getDirection(const Position& point) const override;
		virtual float		getDistance(const Position& point) const override;
		virtual Position	getPosition() const override;

							FastAreaLight(Position position, Color color, float power = 1.0f);
	};
}