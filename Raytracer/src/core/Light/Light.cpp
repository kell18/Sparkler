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

		Collision sunshade = tracer->findAnyCollision(Ray(cpoint, ldir, T_MIN, ldist));
		if (sunshade.isFind) { 
			return Color(0.f);
		}

		Color diffuse  = m.diffuse * max(cos, 0.f);
		vec3 h		   = normalize(ldir - eyeDir);
		float nh	   = max(dot(cnormal, h), 0.f);
		Color specular = m.specular * pow(nh, m.shininess);

		return (diffuse + specular) * color * computeAttenuation(ldist);
	}

	float Light::computeAttenuation(float dist) const
	{
		return power / (_constAttenCoef + _linearAttenCoef * dist + _quadAttenCoef * dist * dist); // std::pow(dist + deadDist, fallof);
	}
	
	Light::Light(Color color, float power)
		: color(color), power(power)
	{
	}

	Light::~Light() 
	{
	}
}
