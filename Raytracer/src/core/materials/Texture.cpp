#include "Texture.h"

namespace raytracer 
{
	Color Texture::getTexelColor(vec2 uvCoords) const
	{
		float x = (textureWidth - 1) * uvCoords.x;
		float y = (textureHeight - 1) * uvCoords.y;
		// TODO: Care with x & y
		RGBQUAD rgbquad;
		FreeImage_GetPixelColor(bitmap, floor(x + 0.5f), floor(y + 0.5f), &rgbquad);
		return Color(rgbquad.rgbRed / 255.f, rgbquad.rgbGreen / 255.f, rgbquad.rgbBlue / 255.f);
	}

	Texture::Texture(string fullPath)
	{
		const char *path = fullPath.c_str();
		bitmap			 = FreeImage_Load(FreeImage_GetFileType(path), path);
		textureWidth	 = FreeImage_GetWidth(bitmap);
		textureHeight	 = FreeImage_GetHeight(bitmap);
		if (bitmap == NULL) {
			cerr << "\nError: texture was not loaded: " << path;
		}
	}

	Texture::~Texture()
	{
		FreeImage_Unload(bitmap);
	}
}