#include "PointLight.h"

namespace raytracer 
{
	Direction PointLight::getDirection(const Position& point) const
	{
		return normalize(point - this->position);
	}

	float PointLight::getDistance(const Position& point) const
	{
		return length(point - this->position);
	}

	Position PointLight::getPosition() const
	{
		return this->position;
	}

	PointLight::PointLight(Position position, Color color, float power)
		: position(position), Light(color, power)
	{
		// Nice and smooth attenuation by distance
		atten.constant = 0.8f;
		atten.linear = 0.004f;
		atten.quad = 0.004f;

		// Attenuation based on cos(angleOfIncidence)
		/*atten.constant = 1.f;
		atten.linear = 0.f;
		atten.quad = 0.f;*/
	}
}