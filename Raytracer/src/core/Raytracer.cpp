#include "Raytracer.h"

namespace raytracer
{
	Color Raytracer::findColor(const Ray &ray, int depth, float refractInd)
	{
		Collision c = findNearestCollision(ray);
		if (!c.isFind) {
			return World::getActiveScene()->bgColor;
		}
		if (Mathf::isAlmostEqual(c.material.emissive, Colors::WHITE, ROUGH_EPS)) {
			return c.material.emissive;
		}

		Material &m		   = c.material;
		Color color		   = m.ambient + m.emissive;
		float reflectRate  = m.reflectRate;
		float transmitRate = m.transmitRate;
		auto lights		   = World::getActiveScene()->lights;

		for (size_t i = 0, len = lights.size(); i < len; ++i) {
			color += lights[i]->computeShadeColor(ray.dir, c);
		}
		color *= c.texel;

		// Trace refracted ray
		float outRefrInd = m.refractInd;
		if (depth > 1 && transmitRate > 0.0f) {
			float n    = refractInd / m.refractInd; // Check
			float cosI = -dot(ray.dir, c.normal);
			// If inside of object: inverse normal and n
			// Also set outRefrInd to air refraction index
			if (cosI < 0.0f) {
				c.normal  *= -1.0f; // Check
				cosI      *= -1.0f;
				n		   = 1.0f / n;
				outRefrInd = 1.0f;
			}

			float sinT = 1.0f + n * n * (cosI * cosI - 1.0f);
			if (sinT >= 0.0f) {
				Direction refrDir = n * ray.dir + (n * cosI - sqrtf(sinT)) * c.normal;
				// TODO: Add color param: Color(0.65f, 0.65f, 1.0f)
				color += transmitRate * findColor(Ray::BuildShifted(c.point, refrDir), 
												  depth - 1, outRefrInd);
			} else {
				// Case of total internal reflection
				// TODO: Bug when ior < 1
				reflectRate += transmitRate;
			}
		}
		// Trace reflected ray
		if (depth > 1 && reflectRate > 0.0f) {
			Direction reflDir = ray.dir - 2.0f * dot(ray.dir, c.normal) * c.normal;
			color +=  reflectRate * m.specular * findColor(Ray::BuildShifted(c.point, reflDir),
															depth - 1, outRefrInd);
		}

		return color;
	}

	Collision Raytracer::findNearestCollision(const Ray &ray)
	{
		Collision nearest;
		Collision current;
		nearest.isFind   = false;
		nearest.distance = FLT_MAX;
		const vector<Primitive*> &primitives = World::getActiveScene()->findNearestPrimitives(ray);
		for (size_t i = 0, len = primitives.size(); i < len; ++i) {
			current = primitives[i]->findIntersectionWith(ray);
			if (current.isFind && current.distance < nearest.distance) { // TODO: May be '<='
				nearest = current;
			}
		}
		return nearest;
	}

	Collision Raytracer::findAnyCollision(const Ray &ray)
	{
		Collision c = { false };
		const vector<Primitive*> &objects = World::getActiveScene()->findNearestPrimitives(ray);
		for (size_t i = 0, len = objects.size(); i < len; ++i) {
			c = objects[i]->findIntersectionWith(ray);
			if (c.isFind) {
				return c;
			}
		}
		return c;
	}
}
