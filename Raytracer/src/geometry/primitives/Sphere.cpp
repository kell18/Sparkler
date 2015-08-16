#include "Sphere.h"

namespace raytracer
{
	// TODO: Try to implement simpler method
	Collision Sphere::findCollisionTo(const Ray &ray) const
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
			if (isTransformed) {
				collision.point  = transforms * cPoint;
				collision.normal = normalize(invTranspTransforms * Direction(cPoint - this->position));
			} else {
				collision.point  = cPoint;
				collision.normal = normalize(cPoint - this->position);
			}
		}
		return collision;
	}

	vec2 Sphere::computeUVCoords(const Collision &c) const
	{
		vec2 uv;
		float phi = atan2f(-c.normal.x, c.normal.y);
		if (phi < 0.0f) {
			phi += two_pi<float>();
		}
		uv.x = (phi) * one_over_two_pi<float>();
		float theta = acosf(c.normal.z);
		uv.y = (pi<float>() - theta) * one_over_pi<float>();
		// TODO: clamp uv btw 0 & 1
		return uv;
	}

	Sphere::Sphere(Position position, float radius)
		: Shape(position), radius(radius)
	{
	}

	Sphere::~Sphere()
	{
	}
}
