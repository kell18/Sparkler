#include "Camera.h"

namespace raytracer
{
	void Camera::lookAt(vec3 lookFrom, vec3 lookTo, vec3 up)
	{
		// We look towards -forward direction
		this->forward = normalize(lookFrom - lookTo);
		this->right   = normalize(cross(up, forward));
		this->up		  = cross(right, forward);
		this->eye	  = lookFrom;
	}

	Ray Camera::rayThroughPixel(float x, float y) const
	{
		// Add & subtract 0.5 bcs I trace ray through center of pixel
		float a = tanHalfFovX * ((x - halfWidth + 0.5f) / (halfWidth));
		float b = tanHalfFovY * ((halfHeight - y - 0.5f) / (halfHeight));

		vec3 dir = normalize(a * right + b * up - forward);

		return Ray(eye, dir);
	}

	Camera::Camera(int width, int height, float fovYDegree)
		: width(width), height(height)
	{
		halfWidth = width / 2.0f;
		halfHeight = height / 2.0f;

		fov.y = radians(fovYDegree);
		fov.x = fov.y * ((float)width) / ((float)height);
		tanHalfFovY = tan (fov.y / 2.0f);
		tanHalfFovX = tanHalfFovY * ((float)width) / ((float)height);
	}
}
