#pragma once


#include "Material.h"

namespace raytracer
{
	class DiffuseMaterial : public Material
	{
	public:
		virtual Color	findSurfaceColor(const Collision &c, float ior,
							int depth, const vec2 &texelCoords = vec2()) const override;

						DiffuseMaterial(MaterialProperties properties);
	};
}
