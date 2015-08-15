#include "Light.h"

namespace raytracer
{
	Color Light::computeShadeColor(const vec3 &eyeDir, const Collision &c) const
	{
		Material m	 = c.material;
		float ldist	 = getDistance(c.point);
		vec3 negLDir = -getDirection(c.point);

		float transmitRate = 1.0f;
		Collision sunshade = Raytracer::findAnyCollision(Ray::BuildShifted(c.point, negLDir, T_MIN, ldist));
		if (sunshade.isFind) {
			if (sunshade.material.transmitRate > 0.0f) {
				transmitRate *= sunshade.material.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}

		float cos	   = dot(c.normal, negLDir);
		Color diffuse  = m.diffuse * max(cos, 0.f);
		vec3 h		   = normalize(negLDir - eyeDir);
		float nh	   = max(dot(c.normal, h), 0.f);
		Color specular = m.specular * pow(nh, m.shininess);
		// cout << "cos: " << cos << endl;

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
