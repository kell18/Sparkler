#include "TexturedObject.h"

namespace raytracer 
{
	Color TexturedObject::getTexelColor(const vec3 &point) const
	{
		return Colors::WHITE;
	}

	bool TexturedObject::loadTexture(string pathAndName)
	{
		isTextured	  = true;
		texture		  = FreeImage_Load(FreeImage_GetFileType(pathAndName.c_str()), pathAndName.c_str());
		textureWidth  = FreeImage_GetWidth(texture);
		textureHeight = FreeImage_GetHeight(texture);
		// if (texture == NULL) cout << "Error: texture was not loaded: " << pathAndName
		return texture != NULL;
	}

	TexturedObject::TexturedObject()
	{
		isTextured = false;
	}

	TexturedObject::~TexturedObject()
	{
		FreeImage_Unload(texture);
	}

}