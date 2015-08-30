#include "Light.h"

namespace raytracer
{
	Color Light::computeShadeColor(const Collision &c, const MaterialProperties &mProperties) const
	{
		float ldist		   = getDistance(c.point);
		Direction negLDir  = -getDirection(c.point);
		float transmitRate = 1.0f;

		DisplayObject *sunshadeDObj = nullptr;
		Collision sunshade = Raytracer::findAnyCollision(
			Ray::BuildShifted(c.point, negLDir, T_MIN, ldist), sunshadeDObj
		);
		if (sunshade.isFind) {
			// TODO: Bug when there are > 1 sunshade on a light path. Change on caustics.
			if (sunshadeDObj->material->properties.transmitRate > 0.0f) {
				transmitRate *= sunshadeDObj->material->properties.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}
		// Determ is it inside of object? If yes then invert norm direction
		Direction normal = dot(c.ray->dir, c.normal) > (-FLT_EPS) ? -c.normal : c.normal;
		float cos		 = dot(normal, negLDir);
		Color diffuse	 = mProperties.diffuse * max(cos, 0.f);
		
		Direction h		 = normalize(negLDir - c.ray->dir);
		float nh		 = max(dot(normal, h), 0.f);
		Color specular	 = mProperties.specular * pow(nh, mProperties.shininess);

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
