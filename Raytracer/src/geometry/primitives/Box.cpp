#include "Box.h"

namespace raytracer 
{
	// TODO: Implement for the end
	Collision Box::findCollisionTo(const Ray & ray) const
	{
		Collision c(ray);		
		Direction invDir = 1.0f / ray.dir;
		float lo = invDir.x*(fromP.x - ray.eye.x);
		float hi = invDir.x*(toP.x - ray.eye.x);
		float tmin = std::min(lo, hi);
		float tmax = std::max(lo, hi);

		float lo1 = invDir.y*(fromP.y - ray.eye.y);
		float hi1 = invDir.y*(toP.y - ray.eye.y);
		tmin = std::max(tmin, std::min(lo1, hi1));
		tmax = std::min(tmax, std::max(lo1, hi1));

		float lo2 = invDir.z*(fromP.z - ray.eye.z);
		float hi2 = invDir.z*(toP.z - ray.eye.z);
		tmin = std::max(tmin, std::min(lo2, hi2));
		tmax = std::min(tmax, std::max(lo2, hi2));

		if ((tmin <= tmax) && (tmax > 0.f)) {
			c.isFind = true;
			c.point = Position(ray.eye + ray.dir * tmin);
			c.distance = tmin;
			// TODO: Find a normal
		}

		return c;
	}

	Box::Box(Position fromPoint, Position toPoint)
		// TODO: change fromPoint to middle
		: Shape(fromPoint), fromP(fromPoint), toP(toPoint)
	{
	}
}