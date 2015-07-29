#include "Light.h"

namespace raytracer
{
	float Light::computeAttenuation(float dist) const
	{
		return power / (_constAttenCoef + _linearAttenCoef * dist + _quadAttenCoef * dist * dist); // std::pow(dist + deadDist, fallof);
	}

	vec3 Light::getDirection(const vec3& point) const
	{
		switch (type)
		{
		case Point:
			return normalize(point - posOrDir);
		case Directional:
			return posOrDir;
		}
	}

	float Light::getDistance(const vec3& point) const
	{
		switch (type)
		{
		case Point:
			return length(point - posOrDir);
		case Directional:
			return 1.f;
		}
	}

	Light::Light(vec3 posOrDir, Color color, float power, LightType type)
		: color(color), power(power), type(type)
	{
		switch (type)
		{
		case Point:
			_constAttenCoef = 0.8f;
			_linearAttenCoef = 0.004f;
			_quadAttenCoef = 0.004f;
			this->posOrDir = posOrDir;
			break;
		case Directional:
			_constAttenCoef = 1.f;
			_linearAttenCoef = 0.f;
			_quadAttenCoef = 0.f;
			this->posOrDir = normalize(posOrDir);
			break;
		}
	}
}
