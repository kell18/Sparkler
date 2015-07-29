#include "Film.h"

namespace raytracer {

	void Film::commitFragment(int x, int y, Color color)
	{
		RGBQUAD rgbquad;
		rgbquad.rgbRed = min(color.r, 1.f) * 255;
		rgbquad.rgbGreen = min(color.g, 1.f) * 255;
		rgbquad.rgbBlue = min(color.b, 1.f) * 255;
		FreeImage_SetPixelColor(_imageBitmap, x, y, &rgbquad);
	};

	void Film::writeToImage(const char *pngImgPathAndName) 
	{
		BOOL isSaved = FreeImage_Save(FIF_PNG, _imageBitmap, pngImgPathAndName, PNG_DEFAULT);
		if (isSaved) {
			cout << "\nImage saved to file: " << pngImgPathAndName << endl;
		} else {
			cout << "\nError: Image not saved" << endl;
			getchar();
		}
	}

	Film::Film(int width, int height, short bitsPerPixel) 
		: _width(width), _height(height)
	{
		_imageBitmap = FreeImage_Allocate(width, height, bitsPerPixel);
		FreeImage_Initialise();
	}

	Film::~Film() {
		FreeImage_DeInitialise();
	}
}