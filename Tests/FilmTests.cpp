#include "FilmTests.h"

TEST_F(FilmTests, CheckRearrangeFragment)
{
	Color origColor(75.f, 90.f, 150.f);
	film->commitFragment(0, 0, origColor);
	RGBQUAD color = film->rearrangeFragment(0, 0);
	float eps = 0.00000001f;
	EXPECT_LT(abs(color.rgbRed - origColor.r), eps);
	EXPECT_LT(abs(color.rgbGreen - origColor.g), eps);
	EXPECT_LT(abs(color.rgbBlue - origColor.b), eps);
}

TEST_F(FilmTests, CheckRearrangeFragmentHDR)
{
	// Code case
	Color origColor(75.f, 900.f, 550.f);
	film->commitFragment(0, 0, origColor);
	RGBQUAD color = film->rearrangeFragment(0, 0);

	// Analitic case
	float red = origColor.r / 900.f * 255.f; // = 21.25
	float green = origColor.g / 900.f * 255.f; // = 255
	float blue = origColor.b / 900.f * 255.f; // = 155.83(3)

	float error = 1.f;
	EXPECT_LT(abs(color.rgbRed - red), error);
	EXPECT_LT(abs(color.rgbGreen - green), error);
	EXPECT_LT(abs(color.rgbBlue - blue), error);
}

TEST_F(FilmTests, CheckWriteToImage)
{
	Color color(75.f, 75.f, 70.f);
	for (int i = 0, len = width; i < len; i++) {
		for (int j = 0; j < height; j++)	{
			film->commitFragment(i, j, color);
		}
	}
	film->writeToImage(fileName);
	EXPECT_TRUE(!!ifstream(fileName));
}
