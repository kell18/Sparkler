#include "Sphere.h"

namespace raytracer
{
	// TODO: Try to implement simpler method
	Collision Sphere::findIntersectionWith(const Ray &ray) const
	{
		Collision collision = {};
		collision.isFind = false;

		vec3 rdir = ray.dir;
		vec3 reye = ray.eye;
		if (isTransformed) {
			// TODO: May be create different classes for pnt and dir
			rdir = vec3(invTransforms * vec4(rdir, 0.f));
			reye = vec3(invTransforms * vec4(reye, 1.f));
		}

		vec3 ec = reye - position;  
		float A = dot(rdir, rdir);
		float B = 2.f * dot(rdir, ec);
		float C = dot(ec, ec) - radius * radius;
		float D = B * B - 4.f * A * C;
		if (D < std::numeric_limits<float>::epsilon()) {
			return collision;
		}

		float A2 = 2.f * A;
		float s1 = - B / A2;
		float s2 = sqrt(D) / A2;
		float t1 = s1 + s2;
		float t2 = s1 - s2;
		float t = 0.f;
		if (t1 > 0 && t2 > 0) {
			t = t1 < t2 ? t1 : t2;
		} else {
			t = t1 > t2 ? t1 : t2;
		}

		if (t > ray.tMin && t < ray.tMax) {
			vec3 cPoint		   = reye + rdir * t;
			collision.isFind   = true;
			collision.distance = t;
			collision.material = material;
			if (isTransformed) {
				collision.point  = vec3(transforms * vec4(cPoint, 1.f));
				collision.normal = normalize(mat3(invTranspTransforms) * (cPoint - position));
			} else {
				collision.point  = cPoint;
				collision.normal = normalize(cPoint - position);
			}
			collision.primitivePos = position;
			collision.texel	       = isTextured ? getTexelColor(collision.normal) : Color(0.f);
		}
		return collision;
	}

	Color Sphere::getTexelColor(const vec3 &pointNormal) const
	{
		float u, v;

		float theta = atan2f(-pointNormal.z, pointNormal.x);
		u = (theta + pi<float>()) / (2.f * pi<float>());

		float phi = acosf(-pointNormal.y / radius);

		// v = phi / pi<float>();

		phi = acosf(pointNormal.y);
		v = 1.f - phi / pi<float>();

		assert(u >= 0.f && v >= 0.f && u < 1.0001f && v < 1.0001f);

		int x = (textureWidth - 1) * u;
		int y = (textureHeight - 1) * v;

		/*y += textureHeight / 4;
		y %= textureHeight;*/

		assert(x >= 0 && y >= 0 && x < textureWidth && y < textureHeight);

		// x = x % textureWidth;
		// y = y % textureHeight;

		// cout << "\n X = " << u << "   Y = ";

		RGBQUAD rgbquad;
		FreeImage_GetPixelColor(texture, x, y, &rgbquad);
		return Color(rgbquad.rgbRed / 255.f, rgbquad.rgbGreen / 255.f, rgbquad.rgbBlue / 255.f); // (v, 0, 0);  // x / ((float)textureWidth-1.f)
	}

	Sphere::Sphere(vec3 position, float radius, Material material)
		: Primitive(position, material), TexturedObject(), radius(radius)
	{
		poleDir	   = normalize(vec3(position.x, position.y, position.z + radius) - position);
		equatorDir = normalize(vec3(position.x + radius, position.y, position.z) - position);
		poleCrossEuqtor = cross(poleDir, equatorDir);
	}

	Sphere::~Sphere()
	{
	}
}
