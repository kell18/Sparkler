#include "FastAreaLight.h"

namespace raytracer 
{
	Color FastAreaLight::computeShadeColor(const Collision &c, 
		const MaterialProperties &mProperties) const
	{
		float ldist = getDistance(c.point);
		Direction negLDir = -getDirection(c.point);
		float transmitRate = 1.0f;

		DisplayObject *sunshadeDObj = nullptr;
		Collision sunshade = Raytracer::findAnyCollision(
			Ray::BuildShifted(c.point, negLDir, T_MIN, ldist), sunshadeDObj
		);
		if (sunshade.isFind) {
			Position primitivePos = sunshadeDObj->shape->getPosition();
			float b = length(sunshade.point - c.point);
			float s = length(primitivePos - sunshade.point);
			float a = length(primitivePos - c.point);
			float cosA = (b*b + s*s - a*a) / (2.f * b * s);

			transmitRate = min(1.0000001f - powf(cosA, 4), 1.0f);
			if (transmitRate < 0.00001f) {
				return Colors::BLACK;
			}
		}
		// Determ is it inside of object? If yes then invert norm direction
		Direction normal = c.normal; // dot(c.ray->dir, c.normal) > (-FLT_EPS) ? -c.normal : c.normal;
		float cos = dot(normal, negLDir);
		Color diffuse = mProperties.diffuse * max(cos, 0.f);

		Direction h = normalize(negLDir - c.ray->dir);
		float nh = max(dot(normal, h), 0.f);
		Color specular = mProperties.specular * pow(nh, mProperties.shininess);

		return transmitRate * (diffuse + specular) * color * computeAttenuation(ldist);
	}

	Direction FastAreaLight::getDirection(const Position & point) const
	{
		return normalize(point - this->position);
	}

	float FastAreaLight::getDistance(const Position & point) const
	{
		return length(point - this->position);
	}

	Position FastAreaLight::getPosition() const
	{
		return this->position;
	}

	FastAreaLight::FastAreaLight(Position position, Color color, float power)
		: Light(color, power), position(position)
	{
		atten.constant = 0.8f;
		atten.linear = 0.004f;
		atten.quad = 0.004f;
	}
}