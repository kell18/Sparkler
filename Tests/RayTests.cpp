#include "RayTests.h"

TEST_F(RayTests, CheckConstructor) 
{
	vec3 eye(1);
	vec3 dir(2);
	Ray ray(eye, dir);
    EXPECT_EQ(ray.eye, eye);
	EXPECT_EQ(ray.dir, dir);
	EXPECT_EQ(ray.tMax, 1000.0f);
}

