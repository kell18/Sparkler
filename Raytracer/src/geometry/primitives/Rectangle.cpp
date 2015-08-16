#include "Rectangle.h"

namespace raytracer 
{

	Collision Rectangle::findCollisionTo(const Ray &ray) const
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
			if (isTransformed) {
				collision.point  = transforms * cPoint;
				collision.normal = normalize(invTranspTransforms * normal);
			} else {
				collision.point  = cPoint;
				collision.normal = normal;
			}
		}
		return collision;
	}

	vec2 Rectangle::computeUVCoords(const Collision &c) const
	{
		vec2 uv;
		// TODO: Get transformed pos
		Position p = (c.point - this->position);
		uv.x = dot(p, aNorm) / aLength;
		uv.y = dot(p, bNorm) / bLength;
		// TODO: clamp uv btw 0 & 1
		return uv;
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

	Rectangle::Rectangle(Position position, Direction a, Direction b)
		: Shape(position), a(a), b(b)
	{
		aLength    = length(a);
		aLengthSqr = aLength * aLength;
		bLength    = length(b);
		bLengthSqr = bLength * bLength;

		normal = cross(a, b) / (aLength * bLength);
		// TODO: Cache this to whole RT
		posDotNorm = dot(this->position, normal);
		aNorm  = a / aLength;
		bNorm  = b / bLength;
	}

}