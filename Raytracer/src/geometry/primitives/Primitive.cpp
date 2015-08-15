#include "Primitive.h"

namespace raytracer
{
	vec3 Primitive::getPosition() const 
	{
		if (isTransformed) {
			// TODO: Change smth...
			return vec3(transforms * vec4(position, 1.0f));
		} else {
			return position;
		}
	}

	void Primitive::transform(mat4 transforms) 
	{
		this->isTransformed		  = true;
		this->transforms			  *= transforms;
		this->invTransforms		  = inverse(transforms);
		this->invTranspTransforms = transpose(invTransforms);
	}

	Primitive::Primitive(vec3 position, Material material)
		: TexturedObject(), position(position), material(material), isTransformed(false)
	{
	}


	Primitive::~Primitive()
	{
	}
}