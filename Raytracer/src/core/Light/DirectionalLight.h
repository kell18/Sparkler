#pragma once 

#include <glm/glm.hpp>
#include "Light.h"

using namespace glm;

namespace raytracer 
{
	class DirectionalLight : public Light
	{
		Direction direction;
	public:
		virtual float		computeAttenuation(float dist) const;

		virtual Direction	getDirection(const Position& point) const;
		virtual float		getDistance(const Position& point) const;
		virtual Position	getPosition() const;

							DirectionalLight(Direction direction, Color color, float power = 1.f);
	};
}