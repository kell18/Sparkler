#pragma once

#include "glm/glm.hpp"
#include "../geometry/primitives/Ray.h"

using namespace glm;

namespace raytracer
{
	class Camera
	{
	public:
		// We look towards -forward direction
		vec3	eye, forward, up, right;
		int		width, height;
		float	halfWidth, halfHeight;
		vec2	fov; // FieldOfView
		float 	tanHalfFovX, tanHalfFovY;

		void	lookAt(vec3 lookFrom, vec3 lookTo, vec3 up);
		Ray		rayThroughPixel(float x, float y) const;

				Camera(int width, int height, float fovYDegree);
	};
}

