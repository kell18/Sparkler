#include "DiffuseMaterial.h"
namespace raytracer
{
	Color DiffuseMaterial::findSurfaceColor(const Collision & c, float envIor, int depth,
		const vec2 & texelCoords) const
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
				color += transmitRate *
					Raytracer::findColor(Ray::BuildShifted(c.point, refrDir), depth - 1, outRefrInd);
			}
			else {
				// Case of total internal reflection
				// TODO: Bug when ior < 1; Take into account 4 variants of outIor
				reflectRate += transmitRate;
			}
		}
		// Trace diffuse reflected rays
		if (depth > 2 && reflectRate > 0.0f) {
			Direction baseRefl = c.ray->dir - 2.0f * rdirDotNorm * c.normal;
			Direction baseX = cross(baseRefl, c.normal); // TODO: Simplify: twist base0
			Direction baseY = cross(baseX, baseRefl);
			Color summColor;
			// cout << "\n\n\n\n\n\n";
			float baseOffs, xOffs, yOffsRange, yOffs;
			for (size_t i = 0; i < properties.diffuseSamples; ++i) {
				baseOffs   = Mathf::randFloat(properties.diffuseRad);
				xOffs	   = (baseOffs - properties.diffuseRad / 2.0f) * 2.0f;
				yOffsRange = properties.diffuseRad - baseOffs;
				yOffs	   = (Mathf::randFloat(yOffsRange) - yOffsRange / 2.0f) * 2.0f;
				/*if ((yOffs + xOffs) * (yOffs + xOffs) > (properties.diffuseRad) * (properties.diffuseRad))
					cout << abs(yOffs + xOffs) - (properties.diffuseRad) << endl;*/
				// cout << xOffs + yOffs << endl;
				Direction reflDir = baseRefl + baseX * xOffs + baseY * yOffs;
				if (dot(reflDir, c.normal) < 0.0f) {
					reflDir = -reflDir - 2.0f * dot(-reflDir, baseRefl) * baseRefl;
				}
				// reflDir = reflDir * powf(dot(baseRefl, reflDir), properties.shininess);
				summColor += reflectRate * properties.specular *
					Raytracer::findColor(Ray(c.point, reflDir), depth - 1, outRefrInd);
			}
			color += summColor / ((float)properties.diffuseSamples);
		}

		return color;
	}

	DiffuseMaterial::DiffuseMaterial(MaterialProperties properties)
		: Material(properties)
	{
	}
}