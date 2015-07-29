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

		virtual Color		getTexelColor(const vec3 &point) const = 0;
		bool				loadTexture(const char* pathAndName);

							TexturedObject();
		virtual				~TexturedObject();
	};
}