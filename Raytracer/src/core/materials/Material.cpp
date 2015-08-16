#include "Material.h"

namespace raytracer
{
	void Material::loadTexture(string fullPath)
	{
		unloadTexture();
		texturePath = fullPath;
		texture		= new Texture(fullPath);
	}

	bool Material::unloadTexture()
	{
		if (texture == nullptr) {
			return false;
		} else {
			delete texture;
			texture = nullptr;
			return true;
		}
	}

	bool Material::isTextured() const
	{
		return texture != nullptr;
	}

	Material::Material(MaterialProperties properties)
		: properties(properties)
	{
		isPureEmissive = Mathf::isAlmostEqual(properties.emissive, Colors::WHITE, ROUGH_EPS);
	}

	Material::~Material()
	{
		unloadTexture();
	}
}
