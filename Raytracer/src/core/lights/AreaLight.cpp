#include "AreaLight.h"

namespace raytracer
{
	Color AreaLight::computeShadeColor(const Collision &c, const MaterialProperties &mProperties) const
	{
		Direction baseDir = rect->getPosition() - c.point;
		Direction deltaX, deltaY;
		Direction localXDir, localYDir;
		Direction lfragmentDir;
		Color color;
		for (int x = 0; x < samples; ++x) {
			deltaX    = rect->getA() * shift * Mathf::randFloat0to1();
			localXDir = rect->getA() * shift * (float)x + deltaX;
			for (int y = 0; y < samples; ++y) {
				deltaY		 = rect->getB() * shift * Mathf::randFloat0to1();
				localYDir	 = rect->getB() * shift * (float)y + deltaY;
				lfragmentDir = baseDir + (localXDir + localYDir);
				color		 += computeFragmentShade(c, mProperties, lfragmentDir);
			}
		}
		return color / samplesSqr;
	}

	Direction AreaLight::getDirection(const Position& point) const
	{
		return normalize(point - rect->getPosition());
	}
		
	float AreaLight::getDistance(const Position& point) const 
	{
		return length(point - rect->getPosition());
	}

	Position AreaLight::getPosition() const
	{
		return rect->getPosition();
	}

	Color AreaLight::computeFragmentShade(const Collision &c, const MaterialProperties &mProperties, const Direction &lfrafmentDir) const
	{
		float ldist	   = length(lfrafmentDir) - 0.0005f;
		Direction ldir = normalize(lfrafmentDir);

		float transmitRate = 1.0f;
		DisplayObject *sunshadeDObject = nullptr;
		Collision sunshade = Raytracer::findAnyCollision(
			Ray::BuildShifted(c.point, ldir, T_MIN, ldist), sunshadeDObject
		);
		if (sunshade.isFind) {
			if (sunshadeDObject->material->properties.transmitRate > 0.0f) {
				transmitRate *= sunshadeDObject->material->properties.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}
		Direction normal = dot(c.ray->dir, c.normal) > (-FLT_EPS) ? -c.normal : c.normal;
		float cos	     = dot(normal, ldir);
		Color diffuse    = mProperties.diffuse * max(cos, 0.f);
		Direction h	     = normalize(ldir - c.ray->dir);
		float nh	     = max(dot(normal, h), 0.f);
		Color specular   = mProperties.specular * pow(nh, mProperties.shininess);

		return transmitRate * (diffuse + specular) * color * computeAttenuation(ldist);
	}

	AreaLight::AreaLight(Color color, Rectangle *rect, int samples, float power)
		: Light(color, power), rect(rect), samples(samples), 
		shift(1.0f / samples), samplesSqr((float) samples * samples)
	{
		if (rect == nullptr) {
			cerr << "Error: area_light Rectangle = nullptr. \
				Note: area_light can use only rectangles as primitive components.";
		}
		atten.constant = 1.0f;
		atten.linear = 0.0f;
		atten.quad = 0.0f;
	}
}