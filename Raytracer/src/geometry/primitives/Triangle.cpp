#include "Triangle.h"

namespace raytracer
{

	Collision Triangle::findCollisionTo(const Ray &ray) const
	{

		Collision collision = {};
		collision.isFind = false;

		Direction rdir = ray.dir;
		Position reye = ray.eye;
		if (isTransformed) {
			rdir = invTransforms * rdir;
			reye = invTransforms * reye;
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

		Position cPoint = reye + rdir * t;
		Direction w	 = cPoint - vert1;
		float w_e1   = dot(w, edge1);
		float w_e2   = dot(w, edge2);
		float e1_e2  = dot(edge1, edge2);
		float e1_e1  = dot(edge1, edge1);
		float e2_e2  = dot(edge2, edge2);
		float denom  = e1_e2 * e1_e2 - e1_e1 * e2_e2;
		float a		 = (e1_e2 * w_e2 - e2_e2 * w_e1) / denom;
		float b		 = (e1_e2 * w_e1 - e1_e1 * w_e2) / denom;

		if (a >= 0.f && b >= 0.f && a + b <= 1.f) {
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

	Direction Triangle::getNormal() const
	{
		if (isTransformed) {
			return transforms * normal;
		} else {
			return normal;
		}
	}

	Position Triangle::getVert1() const
	{
		if (isTransformed) {
			return transforms * vert1;
		} else {
			return vert1;
		}
	}
	Position Triangle::getVert2() const
	{
		if (isTransformed) {
			return transforms * vert2;
		} else {
			return vert2;
		}
	}
	Position Triangle::getVert3() const
	{
		if (isTransformed) {
			return transforms * vert3;
		} else {
			return vert3;
		}
	}

	Triangle::Triangle(Position vert1, Position vert2, Position vert3)
		: Shape(Position((vert1.x + vert2.x + vert3.x) / 3.f, (vert1.y + vert2.y + vert3.y) / 3.f,
					(vert1.z + vert2.z + vert3.z) / 3.f)), 
		vert1(vert1), vert2(vert2), vert3(vert3), 
		edge1(vert2 - vert1), edge2(vert3 - vert1)
	{
		normal =  normalize(cross(edge1, edge2));
	}

	Triangle::~Triangle() 
	{
	}
}