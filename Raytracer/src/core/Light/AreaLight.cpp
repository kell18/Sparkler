#include "AreaLight.h"

namespace raytracer
{
	Color AreaLight::computeShadeColor(const vec3 &eyeDir, const Collision &c) const
	{
		vec3 baseDir = (rect->getPosition() - c.point);
		vec3 deltaX, deltaY;
		vec3 localXDir, localYDir;
		vec3 lrayVect;
		Color color = Colors::BLACK;
		for (int x = 0; x < samples; ++x) {
			deltaX    = rect->getA() * shift * Mathf::randFloat0to1();
			localXDir = rect->getA() * shift * (float)x + deltaX;
			for (int y = 0; y < samples; ++y) {
				deltaY	  = rect->getB() * shift * Mathf::randFloat0to1();
				localYDir = rect->getB() * shift * (float)y + deltaY;
				lrayVect  = baseDir + (localXDir + localYDir);
				color	  += computeFragmentShade(eyeDir, c, lrayVect);
			}
		}
		return color / samplesSqr;
	}

	vec3 AreaLight::getDirection(const vec3& point) const
	{
		return normalize(point - rect->getPosition());
	}
		
	float AreaLight::getDistance(const vec3& point) const 
	{
		return length(point - rect->getPosition());
	}

	vec3 AreaLight::getPosition() const
	{
		return rect->getPosition();
	}

	Color AreaLight::computeFragmentShade(const vec3 &eyeDir, const Collision &c, const vec3 &lrayVect) const
	{
		Material m	= c.material;
		float ldist	= length(lrayVect) - 0.0005f;
		vec3 ldir	= normalize(lrayVect);

		float transmitRate = 1.0f;
		Collision sunshade = Raytracer::findAnyCollision(Ray::BuildShifted(c.point, ldir, T_MIN, ldist));
		if (sunshade.isFind) {
			if (sunshade.material.transmitRate > 0.0f) {
				transmitRate *= sunshade.material.transmitRate * 0.70f;
			} else {
				return Colors::BLACK;
			}
		}
		float cos	   = dot(c.normal, ldir);
		Color diffuse  = m.diffuse * max(cos, 0.f);
		vec3 h		   = normalize(ldir - eyeDir);
		float nh	   = max(dot(c.normal, h), 0.f);
		Color specular = m.specular * pow(nh, m.shininess);

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