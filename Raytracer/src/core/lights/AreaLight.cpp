#include "AreaLight.h"

namespace raytracer
{
	Color AreaLight::computeShadeColor(const Direction &eyeDir, const Collision &c,
		const MaterialProperties &materialProps) const
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
				color		 += computeFragmentShade(eyeDir, c, materialProps, lfragmentDir);
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

	Color AreaLight::computeFragmentShade(const Direction &eyeDir, const Collision &c, 
		const MaterialProperties &materialProps, const Direction &lfrafmentDir) const
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
		float cos	   = dot(c.normal, ldir);
		Color diffuse  = materialProps.diffuse * max(cos, 0.f);
		Direction h	   = normalize(ldir - eyeDir);
		float nh	   = max(dot(c.normal, h), 0.f);
		Color specular = materialProps.specular * pow(nh, materialProps.shininess);

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