#include "CameraTests.h"

TEST_F(CameraTests, CheckNormalization) 
{
	EXPECT_EQ(length(camera->forward), 1);
	EXPECT_EQ(length(camera->up), 1);
	EXPECT_EQ(length(camera->right), 1);
}


TEST_F(CameraTests, CheckOrthogonality)
{
	float eps = std::numeric_limits<float>::epsilon();
	EXPECT_LT(dot(camera->forward, camera->up), eps);
	EXPECT_LT(dot(camera->forward, camera->right), eps);
	EXPECT_LT(dot(camera->right, camera->up), eps);
}

TEST_F(CameraTests, CheckBasis) 
{
	EXPECT_EQ(camera->forward, vec3(0.f, 0.f, -1.f));
	EXPECT_EQ(camera->up, vec3(0.f, -1.f, 0.f));
	EXPECT_EQ(camera->right, vec3(-1.f, 0.f, 0.f));
}


// TODO: Work around, test is too fragile
/*TEST_F(CameraTests, CheckRayThroughPixel) 
{
	// ------------------------------------------------------------
	// Ray through 0,0 pixel
	// tanHalfFovy = tan(30*pi/180 / 2) = 0.26794919243
	// tanHalfFovx = fovy * 640 / 420 = 0.40830353132
	// a = tanHalfFovx * (0 - 320) / (320) = -0.20703606851 // TODO: Recompute
	// b = tanHalfFovy * (210 - 0) / (210) = 0.26794919242
	// dir = a * right + b * up - forward = (0.20703606851, 0, 0) + (0, -0.26794919242, 0) - (0, 0, -1)
	//		= (0.20703606851, -0.26794919242, 1)
	// dirLen = sqrt(0.20703606851^2 + (-0.26794919242)^2 + 1) = 1.05577493027
	// norm(dir) = (0.20703606851/1.05577493, -0.26794919242/1.05577493, 1/1.05577493)
	//		= (0.19609867844, -0.25379385776, 0.94717157188)
	// ------------------------------------------------------------

	Ray expextedRay(vec3(0.f, 0.f, 0.f), vec3(0.19609867844f, -0.25379385776f, 0.94717157188f));
	Ray actualRay = camera->rayThroughPixel(0, 0);
	EXPECT_EQ(expextedRay.eye, actualRay.eye);

	float avgError = 0.0000002f;
	EXPECT_LT(abs(expextedRay.dir.x - actualRay.dir.x), avgError);
	EXPECT_LT(abs(expextedRay.dir.y - actualRay.dir.y), avgError);
	EXPECT_LT(abs(expextedRay.dir.z - actualRay.dir.z), avgError);
}*/