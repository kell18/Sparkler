#include "Raytracer.h"

namespace raytracer
{
	Color Raytracer::findColor(const Ray &ray, int depth, float ior) const
	{
		Collision collision = findNearestCollision(ray);
		if (!collision.isFind) {
			return scene->bgColor;
		}

		Material material  = collision.material;
		vec3 cnormal	   = collision.normal;
		vec3 cpoint		   = collision.point;
		Color color		   = material.ambient + material.emissive;
		float reflectRate  = material.reflectRate;
		float transmitRate = material.transmitRate;
		float refractInd   = ior / material.refractInd;

		for (size_t i = 0, len = lights.size(); i < len; ++i) {
			color += lights[i]->computeShadeColor(ray.dir, collision, this);
		}

		// Trace refracted ray
		if (depth >= 0 && transmitRate > 0.0f) {
			/*if (ior == material.refractInd) {
				color += transmitRate * trace(Ray(cpoint, ray.dir), depth - 1, material.refractInd);
			} else {*/
				float incAngleCos = dot(cnormal, -ray.dir);	
				vec3 normal;
				float outRefrInd;

				// If inside object
				if (incAngleCos < 0.f) {
					incAngleCos *= -1.f;
					normal = -cnormal;
					refractInd = 1.f / refractInd;
					outRefrInd = 1.f;
				} else {
					outRefrInd = material.refractInd;
					normal = cnormal;
				}
				float transAngleCos = 1.f - (1.f / (refractInd * refractInd)) * 
					(1.f - incAngleCos * incAngleCos);
				if (transAngleCos < 0) {
					reflectRate = 1.f; 
				} else {
					transAngleCos = sqrtf(transAngleCos);
					vec3 refrDir = normalize((1.f / refractInd) * (-ray.dir) - 
						(transAngleCos - (1.f / refractInd) * incAngleCos) * normal);
					Color tmpCol = findColor(Ray(cpoint, -refrDir), depth - 1, outRefrInd);
					if (length(tmpCol) > 0.f) {
						// cout << "tmpCol \n";
					}
					color += transmitRate * tmpCol;
				}
			//}
		}
		// Trace reflected ray
		if (depth >= 0 && reflectRate > 0.0f) {
			vec3 eyeDir	 = cpoint - ray.eye;
			vec3 reflDir = normalize(eyeDir - 2.f * dot(eyeDir, cnormal) * cnormal);
			// Rest one material.specular index
			color += material.specular * findColor(Ray(cpoint, reflDir), depth - 1); // reflectRate * 
		}

		return color * collision.texel;
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

	Raytracer::Raytracer(const Scene *scene)
		: scene(scene), lights(scene->lights)
	{
	}

	Raytracer::~Raytracer()
	{
		scene = nullptr;
	}
}
