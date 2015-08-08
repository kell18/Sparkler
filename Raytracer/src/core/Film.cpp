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

	void Film::pushFragments() 
	{
		BOOL isSaved = FreeImage_Save(FIF_PNG, _imageBitmap, outputFile.c_str(), PNG_DEFAULT);
		if (isSaved) {
			cout << "Image saved to file: " << outputFile.c_str() << endl;
		} else {
			cerr << "\nError: Image not saved. Path: " << outputFile.c_str() << endl;
			getchar();
		}
	}

	Film::Film(int width, int height, string outputFile, short bitsPerPixel) 
		: _width(width), _height(height), outputFile(outputFile)
	{
		_imageBitmap = FreeImage_Allocate(width, height, bitsPerPixel);
		FreeImage_Initialise();
	}

	Film::~Film() {
		FreeImage_DeInitialise();
	}
}