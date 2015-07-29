#include "Raytracer.h"

namespace raytracer
{
	Color Raytracer::trace(const Ray &ray, int recursionDepth) const
	{
		Collision collision = cast(ray);
		Color color = scene->bgColor;

		if (collision.isFind) {
			Material material = collision.material;
			vec3 cnormal	  = collision.normal;
			vec3 cpoint		  = collision.point;
			color			  += material.ambient + material.emissive;
			Color lightColor;

			for (size_t i = 0, len = lights.size(); i < len; ++i) {
				Light *light = lights[i];
				float ldist	 = light->getDistance(cpoint);
				vec3 ldir	 = -light->getDirection(cpoint);
				float cos	 = dot(cnormal, ldir);

				float lightAmount = countAmountOfLight(cpoint, ldir, ldist);

				if (lightAmount < 0.00001f || cos <= 0.f) {
					continue;
				}
				Color diffuse = material.diffuse * max(cos, 0.f);
		
				vec3 h		   = normalize(ldir - ray.dir);
				float nh	   = max(dot(cnormal, h), 0.f);
				Color specular = material.specular * pow(nh, material.shininess);

				lightColor += (diffuse + specular) * lightAmount * 
					light->color * light->computeAttenuation(ldist);
			}
			color += collision.texel * lightColor;
			// Trace reflected ray
			if (recursionDepth >= 0 && material.isMirroring) {
				vec3 eye	 = cpoint - ray.eye;
				vec3 r_x	 = dot(eye, cnormal) * cnormal;
				vec3 relfDir = normalize(eye - 2.f * r_x);
				color += material.specular * trace(Ray(cpoint, relfDir), recursionDepth - 1);
			}
			// TODO: Trace refracted ray
		}
		return color;
	}

	Collision Raytracer::cast(const Ray &ray) const
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

	bool Raytracer::isInShadow(vec3 point, vec3 toLightDir, float distToLight) const
	{
		Collision c = { false };
		Ray ray (point, toLightDir);	
		const vector<Primitive*> &objects = scene->findNearestPrimitives(ray);
		for (size_t i = 0, len = objects.size(); i < len; ++i) {
			c = objects[i]->findIntersectionWith(ray);
			if (c.isFind && c.distance < distToLight) {
				return true;
			}
		}
		return false;
	}

	float Raytracer::countAmountOfLight(vec3 point, vec3 toLightDir, float distToLight) const
	{
		Collision c = { false };
		Ray ray (point, toLightDir);	
		const vector<Primitive*> &objects = scene->findNearestPrimitives(ray);
		for (size_t i = 0, len = objects.size(); i < len; ++i) {
			c = objects[i]->findIntersectionWith(ray);
			if (c.isFind && c.distance < distToLight) {
				float b = length(c.point - point);
				float s = length(c.primitivePos - c.point);
				float a = length(c.primitivePos - point);
				float cosA = (b*b + s*s - a*a) / (2.f * b * s);

				if ((cosA > 1.0f || cosA < 0.f) && length(c.point - point) > 2.5f) {
					// cout << "\n cosA = " << cosA << endl;
				}
				return 1.f - powf(cosA, 4);
			}
		}
		return 1.f;
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
