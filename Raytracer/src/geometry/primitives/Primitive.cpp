#include "Primitive.h"

namespace raytracer
{
	Position Primitive::getPosition() const
	{
		if (isTransformed) {
			return transforms * position;
		} else {
			return position;
		}
	}

	void Primitive::transform(mat4 transforms) 
	{
		this->isTransformed		  = true;
		this->transforms		  *= transforms;
		this->invTransforms		  = inverse(transforms);
		this->invTranspTransforms = transpose(invTransforms);
	}

	Primitive::Primitive(Position position, Material material)
		: TexturedObject(), position(position), material(material), isTransformed(false)
	{
	}


	Primitive::~Primitive()
	{
	}
}