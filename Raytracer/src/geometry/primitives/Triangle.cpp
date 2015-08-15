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
		if (Mathf::isAlmostZero(dirn)) {
			return collision;
		}

		float pn   = dot(position, normal);
		float eyen = dot(reye,  normal);
		float t	   = (pn - eyen) / dirn;
		if (t > ray.tMax || t < ray.tMin) {
			return collision;
		}

		vec3 cPoint	= reye + rdir * t;
		vec3 w		= cPoint - vert1;
		float w_e1  = dot(w, edge1);
		float w_e2  = dot(w, edge2);
		float e1_e2 = dot(edge1, edge2);
		float e1_e1 = dot(edge1, edge1);
		float e2_e2 = dot(edge2, edge2);
		float denom = e1_e2 * e1_e2 - e1_e1 * e2_e2;
		float a		= (e1_e2 * w_e2 - e2_e2 * w_e1) / denom;
		float b		= (e1_e2 * w_e1 - e1_e1 * w_e2) / denom;

		if (a >= 0.f && b >= 0.f && a + b <= 1.f) {
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

	vec3 Triangle::getNormal() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(normal, 0.0f));
		} else {
			return normal;
		}
	}

	vec3 Triangle::getVert1() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(vert1, 1.0f));
		} else {
			return vert1;
		}
	}
	vec3 Triangle::getVert2() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(vert2, 1.0f));
		} else {
			return vert2;
		}
	}
	vec3 Triangle::getVert3() const
	{
		if (isTransformed) {
			return vec3(transforms * vec4(vert3, 1.0f));
		} else {
			return vert3;
		}
	}

	Triangle::Triangle(vec3 vert1, vec3 vert2, vec3 vert3, Material material)
		: Primitive(vec3((vert1.x + vert2.x + vert3.x) / 3.f, (vert1.y + vert2.y + vert3.y) / 3.f,
					(vert1.z + vert2.z + vert3.z) / 3.f), material), 
		vert1(vert1), vert2(vert2), vert3(vert3), 
		edge1(vert2 - vert1), edge2(vert3 - vert1)
	{
		normal =  normalize(cross(edge1, edge2));
	}

	Triangle::~Triangle() 
	{
	}
}