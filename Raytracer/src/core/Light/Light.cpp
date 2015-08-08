#include "Light.h"

namespace raytracer
{
	Color Light::computeShadeColor(vec3 eyeDir, const Collision &c, const Raytracer *tracer) const
	{
		Material m	 = c.material;
		vec3 cpoint  = c.point;
		vec3 cnormal = c.normal;
		float ldist	 = getDistance(cpoint);
		vec3 ldir	 = -getDirection(cpoint);
		float cos	 = dot(cnormal, ldir);

		float transmitRate = 1.0f;
		vec3 eye = cpoint + (ldir * COLLISION_AMEND);
		Collision sunshade = tracer->findAnyCollision(Ray(eye, ldir, T_MIN, ldist));
		if (sunshade.isFind) { 
			if (sunshade.material.transmitRate != 0.0f) {
				transmitRate = sunshade.material.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}

		Color diffuse  = m.diffuse * max(cos, 0.f);
		vec3 h		   = normalize(ldir - eyeDir);
		float nh	   = max(dot(cnormal, h), 0.f);
		Color specular = m.specular * pow(nh, m.shininess);

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

	Light::Light(Color color, float power, Attenuation attenuation) 
		: color(color), power(power), atten(attenuation)
	{}

	Light::~Light() 
	{
	}
}
