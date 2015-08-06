#include "PointLight.h"

namespace raytracer 
{

	vec3 PointLight::getDirection(const vec3& point) const
	{
		return normalize(point - position);
	}

	float PointLight::getDistance(const vec3& point) const 
	{
		return length(point - position);
	}

	PointLight::PointLight(vec3 position, Color color, float power)
		: position(position), Light(color, power)
	{
		// Nice and smooth attenuation by distance
		_constAttenCoef = 0.8f;
		_linearAttenCoef = 0.004f;
		_quadAttenCoef = 0.004f;

		// Attenuation based on cos(angleOfIncidence)
		/*_constAttenCoef = 1.0f;
		_linearAttenCoef = 0.0f;
		_quadAttenCoef = 0.0f;*/
	}

}