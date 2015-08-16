#pragma once

#include <glm/glm.hpp>
#include "Light.h"

using namespace glm;

namespace raytracer 
{

	class PointLight : public Light
	{
		Position position;
	public:
		virtual Direction	getDirection(const Position& point) const override;
		virtual float		getDistance(const Position& point) const override;
		virtual Position	getPosition() const override;

							PointLight(Position position, Color color, float power = 1.f);
	};

}