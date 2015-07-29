#include "TexturedObject.h"

namespace raytracer 
{

	bool TexturedObject::loadTexture(const char* pathAndName)
	{
		texture		  = FreeImage_Load(FreeImage_GetFileType(pathAndName), pathAndName);
		textureWidth  = FreeImage_GetWidth(texture);
		textureHeight = FreeImage_GetHeight(texture);
		isTextured	  = true;
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