#pragma once

#include <string.h>
#include "../../utils/Mathf.h"
#include "../../geometry/Collision.h"
#include "../../geometry/primitives/Ray.h"
#include "../World.h"
#include "../Raytracer.h"
#include "MaterialProperties.h"
#include "Texture.h"

using namespace std;

namespace raytracer
{
	class Material
	{
	protected:
	public:
		Texture *texture = nullptr;
		MaterialProperties properties;
		string texturePath;
		bool isPureEmissive;

		virtual Color		findSurfaceColor(const Collision &c, const Ray& ray, float ior,
								int depth, const vec2 &texelCoords = vec2()) const = 0;

							// Unload old texture if exists and load new one
		virtual void		loadTexture(string fullPath);
							// Unload texture if exists. Return true 
							// if there is old texture false otherwise.
		virtual bool		unloadTexture();
		virtual bool		isTextured() const;

							Material(MaterialProperties properties);
		virtual				~Material();
	};
}