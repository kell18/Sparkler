#pragma once 

#include <iostream>
#include <FreeImage.h>
#include <glm/glm.hpp>

#include "../core/Film.h"
#include "Collision.h"

using namespace glm;

namespace raytracer 
{
	class TexturedObject
	{
	public:
		bool isTextured;
		FIBITMAP* texture;
		int textureWidth, textureHeight;

		virtual Color		getTexelColor(const Collision &c) const;
		bool				loadTexture(string pathAndName);

							TexturedObject();
		virtual				~TexturedObject();
	};
}