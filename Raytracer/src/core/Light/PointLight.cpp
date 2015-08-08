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
		atten.constant = 0.8f;
		atten.linear = 0.004f;
		atten.quad = 0.004f;

		// Attenuation based on cos(angleOfIncidence)
		/*atten.constant = 1.f;
		atten.linear = 0.f;
		atten.quad = 0.f;*/
	}

	PointLight::PointLight(vec3 position, Color color, Attenuation attn, float power)
		: position(position), Light(color, power, attn)
	{
	}

}