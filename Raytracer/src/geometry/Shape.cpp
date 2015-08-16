#include "Shape.h"

namespace raytracer 
{
	void Shape::transform(mat4 transforms)
	{
		this->isTransformed = true;
		this->transforms *= transforms;
		this->invTransforms = inverse(transforms);
		this->invTranspTransforms = transpose(invTransforms);
	}
	
	Position Shape::getPosition() const
	{
		if (isTransformed) {
			return transforms * position;
		}
		else {
			return position;
		}
	}

	vec2 Shape::computeUVCoords(const Collision &c) const
	{
		// TODO: Make pure virtual
		return vec2(0.0f);
	}

	Shape::Shape(Position position)
		: position(position), isTransformed(false)
	{
	}

	Shape::~Shape()
	{
	}
}