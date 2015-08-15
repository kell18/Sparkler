#pragma once

#include "../utils/Mathf.h"
#include "../geometry/primitives/Ray.h"

namespace raytracer
{
	class Camera
	{
	public:
		// We look towards -forward direction
		Position	eye;
		Direction	forward, up, right;
		int			width, height;
		float		halfWidth, halfHeight;
		vec2		fov; // FieldOfView
		float 		tanHalfFovX, tanHalfFovY;

		void	lookAt(Position lookFrom, Position lookTo, Direction up);
		Ray		rayThroughPixel(float x, float y) const;

				Camera(int width, int height, float fovYDegree);
	};
}

