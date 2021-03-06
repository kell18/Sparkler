#pragma once

#include "Material.h"

namespace raytracer 
{
	class SimpleMaterial : public Material
	{
	public:
		virtual Color		findSurfaceColor(const Collision &c, float envIor,
								int depth, const vec2 &texelCoords = vec2()) const override;

							SimpleMaterial(MaterialProperties properties);
	};
}