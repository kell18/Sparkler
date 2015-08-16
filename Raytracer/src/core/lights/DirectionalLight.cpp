#include "DirectionalLight.h"

namespace raytracer 
{
	float DirectionalLight::computeAttenuation(float dist) const
	{
		return power;
	}

	Direction DirectionalLight::getDirection(const Position& point) const
	{
		return direction;
	}

	float DirectionalLight::getDistance(const Position& point) const 
	{
		return 1.f;
	}

	Position DirectionalLight::getPosition() const 
	{
		cout << "\nWarning: taking position of directional light.";
		return Position();
	}

	DirectionalLight::DirectionalLight(Direction direction, Color color, float power)
		: direction(normalize(direction)), Light(color, power)
	{
		atten.constant = 1.f;
		atten.linear = 0.f;
		atten.quad = 0.f;
	}
}