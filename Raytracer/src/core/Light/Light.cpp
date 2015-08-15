#include "Light.h"

namespace raytracer
{
	Color Light::computeShadeColor(const Direction &eyeDir, const Collision &c) const
	{
		float ldist		   = getDistance(c.point);
		Direction negLDir  = -getDirection(c.point);
		float transmitRate = 1.0f;

		Collision sunshade = Raytracer::findAnyCollision(
			Ray::BuildShifted(c.point, negLDir, T_MIN, ldist)
		);
		if (sunshade.isFind) {
			if (sunshade.material.transmitRate > 0.0f) {
				transmitRate *= sunshade.material.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}

		float cos	   = dot(c.normal, negLDir);
		Color diffuse  = c.material.diffuse * max(cos, 0.f);
		Direction h	   = normalize(negLDir - eyeDir);
		float nh	   = max(dot(c.normal, h), 0.f);
		Color specular = c.material.specular * pow(nh, c.material.shininess);
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
