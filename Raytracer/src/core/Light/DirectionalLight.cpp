#include "DirectionalLight.h"

namespace raytracer 
{

	float DirectionalLight::computeAttenuation(float dist) const
	{
		return power;
	}

	vec3 DirectionalLight::getDirection(const vec3& point) const 
	{
		return direction;
	}

	float DirectionalLight::getDistance(const vec3& point) const 
	{
		return 1.f;
	}

	DirectionalLight::DirectionalLight(vec3 direction, Color color, float power)
		: direction(normalize(direction)), Light(color, power)
	{
		_constAttenCoef = 1.f;
		_linearAttenCoef = 0.f;
		_quadAttenCoef = 0.f;
	}

}