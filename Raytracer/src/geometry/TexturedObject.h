#pragma once 

#include <iostream>
#include <FreeImage.h>
#include <glm/glm.hpp>

#include "../core/Film.h"

using namespace glm;

namespace raytracer 
{
	class TexturedObject
	{
	public:
		bool isTextured;
		FIBITMAP* texture;
		int textureWidth, textureHeight;

		virtual Color		getTexelColor(const vec3 &point) const;
		bool				loadTexture(string pathAndName);

							TexturedObject();
		virtual				~TexturedObject();
	};
}