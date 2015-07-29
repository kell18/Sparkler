#include "Primitive.h"

namespace raytracer
{
	void Primitive::transform(mat4 transforms) 
	{
		this->isTransformed		  = true;
		this->transforms			  *= transforms;
		this->invTransforms		  = inverse(transforms);
		this->invTranspTransforms = transpose(invTransforms);
	}

	Primitive::Primitive(vec3 position, Material material)
		: position(position), material(material), isTransformed(false)
	{
	}


	Primitive::~Primitive()
	{
	}
}