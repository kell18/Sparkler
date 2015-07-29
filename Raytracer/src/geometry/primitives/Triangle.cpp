#include "Triangle.h"

namespace raytracer
{

	Collision Triangle::findIntersectionWith(const Ray &ray) const
	{

		Collision collision = {};
		collision.isFind = false;

		vec3 rdir = ray.dir;
		vec3 reye = ray.eye;
		if (isTransformed) {
			rdir = vec3(invTransforms * vec4(rdir, 0.f));
			reye = vec3(invTransforms * vec4(reye, 1.f));
		}

		float dirn = dot(rdir, normal);
		if (dirn == 0) {
			return collision;
		}

		float pn   = dot(position, normal);
		float eyen = dot(reye,  normal);
		float t	   = (pn - eyen) / dirn;
		if (t > ray.tMax || t < ray.tMin) {
			return collision;
		}

		vec3 cPoint	= reye + rdir * t;
		vec3 w		= cPoint - p1;
		float w_v1  = dot(w, v1);
		float w_v2  = dot(w, v2);
		float v1_v2 = dot(v1, v2);
		float v1_v1 = dot(v1, v1);
		float v2_v2 = dot(v2, v2);
		float denom = v1_v2 * v1_v2 - v1_v1 * v2_v2;
		float a		= (v1_v2 * w_v2 - v2_v2 * w_v1) / denom;
		float b		= (v1_v2 * w_v1 - v1_v1 * w_v2) / denom;

		if (a > 0.f && b > 0.f && a + b <= 1.f) { // ...
			collision.isFind	= true;
			collision.distance  = t;
			collision.material  = material;
			if (isTransformed) {
				collision.point  = vec3(transforms * vec4(cPoint, 1.f));
				collision.normal = normalize(mat3(invTranspTransforms) * normal);
			} else {
				collision.point  = cPoint;
				collision.normal = normal;
			}
			collision.primitivePos = position;
		}

		return collision;
	}

	Triangle::Triangle(vec3 p1, vec3 p2, vec3 p3, Material material)
		: Primitive(vec3((p1.x + p2.x + p3.x) / 3.f, (p1.y + p2.y + p3.y) / 3.f,
					(p1.z + p2.z + p3.z) / 3.f), material), 
		p1(p1), p2(p2), p3(p3), 
		v1(p2 - p1), v2(p3 - p1)
	{
		normal =  normalize(cross(v1, v2));
	}

	Triangle::~Triangle() 
	{
	}
}