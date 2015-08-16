#pragma once

#include <string.h>
#include <iostream>
#include <FreeImage.h>
#include <glm/glm.hpp>

#include "../../utils/Color.h"

using namespace std;

namespace raytracer 
{
	class Texture
	{
	protected:
		FIBITMAP* bitmap;
	public:
		int textureWidth, textureHeight;

		virtual Color		getTexelColor(vec2 uvCoords) const;

							Texture(string fullPath);
		virtual				~Texture();
	};
}
