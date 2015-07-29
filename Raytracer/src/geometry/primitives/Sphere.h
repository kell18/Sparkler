#pragma once

#include <type_traits>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../../utils/Constants.h"
#include "Primitive.h"
#include "../TexturedObject.h"
#include "../Material.h"
#include "../Collision.h"

using namespace glm;

namespace raytracer
{
	class Sphere : public Primitive, public TexturedObject
	{
	public:
		vec3 poleDir, equatorDir;
		vec3 poleCrossEuqtor;
		float maxc, minc;
		float radius;

		virtual Collision	findIntersectionWith(const Ray &ray) const;

		virtual Color		getTexelColor(const vec3 &pointNormal) const;

							Sphere(vec3 position, float radius, Material material);
		virtual				~Sphere();
	};

}
