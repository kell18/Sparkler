#include "SimpleMaterial.h"

namespace raytracer 
{
	Color SimpleMaterial::findSurfaceColor(const Collision &c, float envIor,  
		int depth, const vec2 &texelCoords) const
	{
		if (isPureEmissive) {
			return properties.emissive;
		}
		Color color = properties.ambient + properties.emissive;
		float reflectRate = properties.reflectRate;
		float transmitRate = properties.transmitRate;
		float rdirDotNorm = dot(c.ray->dir, c.normal);
		auto lights = World::getActiveScene()->lights;

		for (size_t i = 0, len = lights.size(); i < len; ++i) {
			color += lights[i]->computeShadeColor(c, properties);
		}
		if (isTextured()) {
			color *= texture->getTexelColor(texelCoords);
		}
		// Trace refracted ray
		float outRefrInd = properties.refractInd;
		if (depth > 1 && transmitRate > 0.0f) {
			float n = envIor / properties.refractInd; // Check
			Direction normal = c.normal;
			float cosI = -rdirDotNorm;
			if (cosI < 0.0f) {
				normal *= -1.0f; // Check
				cosI *= -1.0f;
				n = 1.0f / n;
				outRefrInd = 1.0f;
			}

			float sinT = 1.0f + n * n * (cosI * cosI - 1.0f);
			if (sinT >= 0.0f) {
				Direction refrDir = n * c.ray->dir + (n * cosI - sqrtf(sinT)) * normal;// c.normal
				// TODO: Add color param: Color(0.65f, 0.65f, 1.0f)
				color += transmitRate * 
					Raytracer::findColor(Ray::BuildShifted(c.point, refrDir), depth - 1, outRefrInd);
			}
			else {
				// Case of total internal reflection
				// TODO: Bug when ior < 1; Take into account 4 variants of outIor
				reflectRate += transmitRate;
			}
		}
		// Trace reflected ray
		if (depth > 1 && reflectRate > 0.0f) {
			Direction reflDir = c.ray->dir - 2.0f * rdirDotNorm * c.normal;
			color += reflectRate * properties.specular * 
				Raytracer::findColor(Ray::BuildShifted(c.point, reflDir), depth - 1, outRefrInd);
		}

		return color;
	}

	SimpleMaterial::SimpleMaterial(MaterialProperties properties)
		: Material(properties)
	{
	}

	SimpleMaterial::~SimpleMaterial()
	{
	}
}