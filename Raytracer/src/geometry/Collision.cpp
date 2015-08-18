#include "Collision.h"

namespace raytracer 
{
	Collision::Collision()
		: isFind(false), distance(FLT_MAX)
	{
	}

	Collision::Collision(const Ray &ray) 
		: ray(&ray), isFind(false), distance(FLT_MAX)
	{
	}

	/*Collision::Collision(const Collision &c)
		: ray(c.ray), isFind(c.isFind), distance(c.distance),
		point(c.point), normal(c.normal), rdirDotNorm(c.rdirDotNorm)
	{
	}

	Collision &	Collision::operator= (const Collision &other) 
	{
		*this = Collision(other);
		return *this;
	}*/
}