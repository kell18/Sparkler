#include "Raytracer.h"

namespace raytracer
{
	Color Raytracer::findColor(const Ray &ray, int depth, float refractInd) const
	{
		Collision c = findNearestCollision(ray);
		if (!c.isFind) {
			return scene->bgColor;
		}

		Material &m		   = c.material;
		Color color		   = m.ambient;
		float reflectRate  = m.reflectRate;
		float transmitRate = m.transmitRate;
		vec3 specularity   = m.specular;

		for (size_t i = 0, len = lights.size(); i < len; ++i) {
			color += lights[i]->computeShadeColor(ray.dir, c, this);
		}
		color *= c.texel;

		// Trace refracted ray
		float outRefrInd = 1.0f;
		if (depth >= 0 && transmitRate > 0.0f) {
			float n = refractInd / m.refractInd; // Check
			float outRefrInd = m.refractInd;

			float cosI = -dot(ray.dir, c.normal);
			if (cosI < 0.0f) {    // Inside of object
				c.normal *= -1.0f;
				cosI   *= -1.0f;
				n = 1.0f / n; // m.refractInd; // or m.refractInd / 1.0f bcs we assume that outRefrInd is air
				outRefrInd = 1.0f;
			}

			float sinT = 1.0f + n * n * (cosI * cosI - 1.0f);
			if (sinT > 0.0f) {
				vec3 refrDir = n * ray.dir + (n * cosI - sqrtf(sinT)) * c.normal;
				vec3 refrEye = c.point + (refrDir * COLLISION_AMEND);
				// TODO: Add color param: Color(0.65f, 0.65f, 1.0f)
				color += transmitRate * findColor(Ray(refrEye, refrDir), depth - 1, outRefrInd);
			} else {
				reflectRate += transmitRate;
			}
		}

		// Trace reflected ray
		if (depth >= 0 ) {
			vec3 reflDir = ray.dir - 2.f * dot(ray.dir, c.normal) * c.normal;
			vec3 reflEye = c.point + (reflDir * COLLISION_AMEND);
			color +=  specularity * findColor(Ray(reflEye, reflDir), depth - 1, outRefrInd);		
		}

		return color;
	}

	Collision Raytracer::findNearestCollision(const Ray &ray) const
	{
		Collision nearest;
		Collision current;
		nearest.isFind   = false;
		nearest.distance = FLT_MAX;
		const vector<Primitive*> &primitives = scene->findNearestPrimitives(ray);
		for (size_t i = 0, len = primitives.size(); i < len; ++i) {
			current = primitives[i]->findIntersectionWith(ray);
			if (current.isFind && current.distance < nearest.distance) { // TODO: May be '<='
				nearest = current;
			}
		}
		return nearest;
	}

	Collision Raytracer::findAnyCollision(const Ray &ray) const
	{
		Collision c = { false };
		const vector<Primitive*> &objects = scene->findNearestPrimitives(ray);
		for (size_t i = 0, len = objects.size(); i < len; ++i) {
			c = objects[i]->findIntersectionWith(ray);
			if (c.isFind) {
				return c;
			}
		}
		return c;
	}

	Raytracer::Raytracer(const Scene *scene, int maxDepth)
		: scene(scene), lights(scene->lights), maxDepth(maxDepth)
	{
	}

	Raytracer::~Raytracer()
	{
		scene = nullptr;
	}
}
