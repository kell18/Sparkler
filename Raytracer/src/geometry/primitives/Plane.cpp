#include "Plane.h"

namespace raytracer
{
	Collision Plane::findIntersectionWith(const Ray &ray) const
	{
		Collision c = {};
		c.isFind = false;

		vec3 rdir = ray.dir;
		vec3 reye = ray.eye;
		if (isTransformed) {
			rdir = vec3(invTransforms * vec4(rdir, 0.f));
			reye = vec3(invTransforms * vec4(reye, 1.f));
		}

		float dirn = dot(rdir, normal);
		if (Mathf::isAlmostZero(dirn)) {
			return c;
		}
		float pn   = dot(position, normal);
		float eyen = dot(reye,  normal);
		float t	   = (pn - eyen) / dirn;

		if (t < ray.tMax && t > ray.tMin) {
			vec3 cPoint = reye + rdir * t;
			c.isFind	= true;
			c.distance  = t;
			c.material  = material;
			c.texel		= getTexelColor(cPoint);
			if (isTransformed) {
				c.point  = vec3(transforms * vec4(cPoint, 1.f));
				c.normal = normalize(mat3(invTranspTransforms) * normal);
			} else {
				c.point  = cPoint;
				c.normal = normal;
			}
		}
		return c;
	}

	vec3 Plane::getNormal() const 
	{
		if (isTransformed) {
			return vec3(transforms * vec4(normal, 0.0f));
		} else {
			return normal;
		}
	}

	Plane::Plane(vec3 position, vec3 normal, Material material)
		: Primitive(position, material), normal(normal)
	{
	}

	Plane::~Plane()
	{
	}
}
