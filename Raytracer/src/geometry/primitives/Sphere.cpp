#include "Sphere.h"

namespace raytracer
{
	// TODO: Try to implement simpler method
	Collision Sphere::findIntersectionWith(const Ray &ray) const
	{
		Collision collision = {};
		collision.isFind = false;
		
		Direction rdir = ray.dir;
		Position reye = ray.eye;
		if (isTransformed) {
			rdir = invTransforms * rdir;
			reye = invTransforms * reye;
		}

		Direction ec = reye - this->position;  
		float A = dot(rdir, rdir);
		float B = 2.f * dot(rdir, ec);
		float C = dot(ec, ec) - radius * radius;
		float D = B * B - 4.f * A * C;
		if (D < std::numeric_limits<float>::epsilon()) {
			return collision;
		}

		float A2 = 2.f * A;
		float s1 = - B / A2;
		float s2 = sqrt(D) / A2;
		float t1 = s1 + s2;
		float t2 = s1 - s2;
		float t = 0.f;
		if (t1 > 0.f && t2 > 0.f) {
			t = t1 < t2 ? t1 : t2;
		} else {
			t = t1 > t2 ? t1 : t2;
		}

		if (t > ray.tMin && t < ray.tMax) {
			Position cPoint	   = reye + rdir * t;
			collision.isFind   = true;
			collision.distance = t;
			collision.material = material;
			if (isTransformed) {
				collision.point  = transforms * cPoint;
				collision.normal = normalize(invTranspTransforms * Direction(cPoint - this->position));
			} else {
				collision.point  = cPoint;
				collision.normal = normalize(cPoint - this->position);
			}
			collision.texel	= getTexelColor(collision);
		}
		return collision;
	}

	Color Sphere::getTexelColor(const Collision &c) const
	{
		if (!isTextured) {
			return Colors::WHITE;
		}
		float phi = atan2f(-c.normal.x, c.normal.y);
		if (phi < 0.0f) {
			phi += two_pi<float>();
		}
		float u	  = (phi) * one_over_two_pi<float>();
		float theta = acosf(c.normal.z);
		float v		= (pi<float>() - theta) * one_over_pi<float>();

		int x = (textureWidth - 1) * u;
		int y = (textureHeight - 1) * v;
		RGBQUAD rgbquad;
		FreeImage_GetPixelColor(texture, x, y, &rgbquad);
		return Color(rgbquad.rgbRed / 255.f, rgbquad.rgbGreen / 255.f, rgbquad.rgbBlue / 255.f); 
	}

	Sphere::Sphere(Position position, float radius, Material material)
		: Primitive(position, material), radius(radius)
	{
	}

	Sphere::~Sphere()
	{
	}
}
