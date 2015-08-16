#include "Plane.h"

namespace raytracer
{
	Collision Plane::findCollisionTo(const Ray &ray) const
	{
		Collision c = {};
		c.isFind = false;

		Position reye = ray.eye;
		Direction rdir = ray.dir;
		if (isTransformed) {
			rdir = invTransforms * rdir;
			reye = invTransforms * reye;
		}

		float dirn = dot(rdir, normal);
		if (Mathf::isAlmostZero(dirn)) {
			return c;
		}
		float pn   = dot(position, normal);
		float eyen = dot(reye,  normal);
		float t	   = (pn - eyen) / dirn;

		if (t < ray.tMax && t > ray.tMin) {
			Position cPoint = reye + rdir * t;
			c.isFind	 = true;
			c.distance   = t;
			if (isTransformed) {
				c.point  = transforms * cPoint;
				c.normal = normalize(invTranspTransforms * normal);
			} else {
				c.point  = cPoint;
				c.normal = normal;
			}
		}
		return c;
	}

	Direction Plane::getNormal() const
	{
		if (isTransformed) {
			return transforms * normal;
		} else {
			return normal;
		}
	}

	Plane::Plane(Position position, Direction normal)
		: Shape(position), normal(normal)
	{
	}

	Plane::~Plane()
	{
	}
}
