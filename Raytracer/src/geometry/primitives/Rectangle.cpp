#include "Rectangle.h"

namespace raytracer 
{

	Collision Rectangle::findIntersectionWith(const Ray &ray) const
	{
		Collision collision;
		collision.isFind = false;

		vec3 rdir = ray.dir;
		vec3 reye = ray.eye;
		if (isTransformed) {
			rdir = vec3(invTransforms * vec4(rdir, 0.f));
			reye = vec3(invTransforms * vec4(reye, 1.f));
		}

		float dirn = dot(rdir, normal);
		if (Mathf::isAlmostZero(dirn)) {
			return collision;
		}
		float pn   = dot(position, normal);
		float eyen = dot(reye,  normal);
		float t	   = (pn - eyen) / dirn;
		if (t > ray.tMax || t < ray.tMin) {
			return collision;
		}

		vec3 cPoint = reye + rdir * t;
		vec3 p		= cPoint - position;
		float pDotA = dot(p, a);
		float pDotB = dot(p, b);
		if (pDotA >= 0.f && pDotA <= aLengthSqr && pDotB >= 0.f && pDotB <= bLengthSqr)
		{
			collision.isFind   = true;
			collision.distance = t;
			collision.material = material;
			collision.texel	   = getTexelColor(cPoint);
			if (isTransformed) {
				collision.point  = vec3(transforms * vec4(cPoint, 1.f));
				collision.normal = normalize(mat3(invTranspTransforms) * normal);
			} else {
				collision.point  = cPoint;
				collision.normal = normal;
			}
		}
		return collision;
	}

	Color Rectangle::getTexelColor(const vec3 &point) const
	{
		if (!isTextured) {
			return Colors::WHITE;
		}
		// TODO: Get transformed pos
		vec3 p = (point - (this->position));
		float u = dot(p, aNorm) / aLength;
		float v = dot(p, bNorm) / bLength;
		// assert(dot(p, aNorm) > 0.0f && dot(p, bNorm) > 0.0f);
		// assert(u > 0.f && v > 0.f && u < 1.0001f && v < 1.0001f);
		float x = (textureWidth - 1) * u;
		float y = (textureHeight - 1) * v;

		RGBQUAD rgbquad;
		FreeImage_GetPixelColor(texture, x, y, &rgbquad);
		return Color(rgbquad.rgbRed / 255.f, rgbquad.rgbGreen / 255.f, rgbquad.rgbBlue / 255.f);
	}

	vec3 Rectangle::getA() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(a, 0.0f));
		} else {
			return a;
		}
	}

	vec3 Rectangle::getB() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(b, 0.0f));
		} else {
			return b;
		}
	}

	Rectangle::Rectangle(vec3 position, vec3 a, vec3 b, Material material) 
		: Primitive(position, material), a(a), b(b)
	{
		aLength    = length(a);
		aLengthSqr = aLength * aLength;
		bLength    = length(b);
		bLengthSqr = bLength * bLength;

		normal = cross(a, b) / (aLength * bLength);
		aNorm  = a / aLength;
		bNorm  = b / bLength;
	}

}