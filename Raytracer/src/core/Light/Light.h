#pragma once

#include "../../utils/Mathf.h"
#include "../../utils/Color.h"
#include "../../geometry/Collision.h"
#include "../Film.h"
#include "../Raytracer.h"
#include "../../geometry/primitives/Ray.h"

namespace raytracer
{
	class Raytracer;

	struct Attenuation
	{
		float constant;
		float linear;
		float quad;
	};

	class Light
	{
	public:
		Attenuation atten;
		Color color;
		float power;

		virtual Color		computeShadeColor(const Direction &eyeDir, const Collision &c) const;
		virtual float		computeAttenuation(float dist) const;

		virtual Direction	getDirection(const Position& point) const = 0;
		virtual float		getDistance(const Position& point) const = 0;
		virtual Position	getPosition() const = 0;

							Light(Color color, float power);
		virtual				~Light();
	};
}

