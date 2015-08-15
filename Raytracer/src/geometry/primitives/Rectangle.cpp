#include "Rectangle.h"

namespace raytracer 
{

	Collision Rectangle::findIntersectionWith(const Ray &ray) const
	{
		Collision collision;
		collision.isFind = false;

		Position reye = ray.eye;
		Direction rdir = ray.dir;
		if (isTransformed) {
			reye = invTransforms * reye;
			rdir = invTransforms * rdir;
		}

		float dirn = dot(rdir, normal);
		if (Mathf::isAlmostZero(dirn)) {
			return collision;
		}
		float eyen = dot(reye,  normal);
		float t	   = (posDotNorm - eyen) / dirn;
		if (t > ray.tMax || t < ray.tMin) {
			return collision;
		}

		Position cPoint = reye + rdir * t;
		Direction p	 = cPoint - this->position;
		float pDotA  = dot(p, a);
		float pDotB  = dot(p, b);
		if (pDotA >= 0.f && pDotA <= aLengthSqr && pDotB >= 0.f && pDotB <= bLengthSqr)
		{
			collision.isFind   = true;
			collision.distance = t;
			collision.material = material;
			if (isTransformed) {
				collision.point  = transforms * cPoint;
				collision.normal = normalize(invTranspTransforms * normal);
			} else {
				collision.point  = cPoint;
				collision.normal = normal;
			}
			collision.texel	= getTexelColor(collision);
		}
		return collision;
	}

	Color Rectangle::getTexelColor(const Collision &c) const
	{
		if (!isTextured) {
			return Colors::WHITE;
		}
		// TODO: Get transformed pos
		Position p = (c.point - this->position);
		float u = dot(p, aNorm) / aLength;
		float v = dot(p, bNorm) / bLength;
		// assert(dot(p, aNorm) > 0.0f && dot(p, bNorm) > 0.0f);
		// assert(u > 0.f && v > 0.f && u < 1.0001f && v < 1.0001f);
		float x = (textureWidth - 1) * u;
		float y = (textureHeight - 1) * v;

		RGBQUAD rgbquad;
		FreeImage_GetPixelColor(texture, floor(x+0.5f), floor(y+0.5f), &rgbquad);
		return Color(rgbquad.rgbRed / 255.f, rgbquad.rgbGreen / 255.f, rgbquad.rgbBlue / 255.f);
	}

	Direction Rectangle::getA() const
	{
		if (isTransformed) {
			return transforms * a;
		} else {
			return a;
		}
	}

	Direction Rectangle::getB() const
	{
		if (isTransformed) {
			return transforms * b;
		} else {
			return b;
		}
	}

	Rectangle::Rectangle(Position position, Direction a, Direction b, Material material)
		: Primitive(position, material), a(a), b(b)
	{
		aLength    = length(a);
		aLengthSqr = aLength * aLength;
		bLength    = length(b);
		bLengthSqr = bLength * bLength;

		normal = cross(a, b) / (aLength * bLength);
		posDotNorm = dot(this->position, normal);
		aNorm  = a / aLength;
		bNorm  = b / bLength;
	}

}