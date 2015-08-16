#include "Light.h"

namespace raytracer
{
	Color Light::computeShadeColor(const Direction &eyeDir, const Collision &c, 
		const MaterialProperties &materialProps) const
	{
		float ldist		   = getDistance(c.point);
		Direction negLDir  = -getDirection(c.point);
		float transmitRate = 1.0f;

		DisplayObject *sunshadeDObj = nullptr;
		Collision sunshade = Raytracer::findAnyCollision(
			Ray::BuildShifted(c.point, negLDir, T_MIN, ldist), sunshadeDObj
		);
		if (sunshade.isFind) {
			if (sunshadeDObj->material->properties.transmitRate > 0.0f) {
				transmitRate *= sunshadeDObj->material->properties.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}

		float cos	   = dot(c.normal, negLDir);
		Color diffuse  = materialProps.diffuse * max(cos, 0.f);
		Direction h	   = normalize(negLDir - eyeDir);
		float nh	   = max(dot(c.normal, h), 0.f);
		Color specular = materialProps.specular * pow(nh, materialProps.shininess);
		// cout << "cos: " << cos << endl;

		if (World::getWorkTime() > 1000) {
			//cout << "\nc.normal.x: " << c.normal << " negLDir.x: " << negLDir << " cos: " << cos;
		}

		return transmitRate * (diffuse + specular) * color * computeAttenuation(ldist);
	}

	float Light::computeAttenuation(float dist) const
	{
		return power / (atten.constant + atten.linear * dist + atten.quad * dist * dist);
		// some variations: std::pow(dist + deadDist, fallof);
	}
	
	Light::Light(Color color, float power)
		: color(color), power(power)
	{
	}

	Light::~Light() 
	{
	}
}
