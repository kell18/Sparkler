#include "Film.h"

namespace raytracer {

	void Film::commitFragment(int x, int y, Color color)
	{
		RGBQUAD rgbquad;
		rgbquad.rgbRed = min(color.r, 1.f) * 255;
		rgbquad.rgbGreen = min(color.g, 1.f) * 255;
		rgbquad.rgbBlue = min(color.b, 1.f) * 255;
		FreeImage_SetPixelColor(raw_imageBitmap, x, y, &rgbquad);
	};

	void Film::pushFragments() 
	{
		BOOL isSaved = FreeImage_Save(FIF_PNG, raw_imageBitmap, outputFile.c_str(), PNG_DEFAULT);
		if (isSaved) {
			cout << "Image saved to file: " << outputFile.c_str() << endl;
		} else {
			cerr << "\nError: Image not saved. Path: " << outputFile.c_str() << endl;
			getchar();
		}
	}

	void Film::logProgress(int param)
	{
		if (param % logInterval == 0) {
			int percents = param / logInterval + 1;
			progressMsg += "=";
			cout << "Progress: [" << progressMsg << ">" <<
				setw(logFrequency + 2 - percents) << "] " << percents * 5 << "%\r";
		}
	}

	Film::Film(int width, int height, string outputFile, short bitsPerPixel) 
		: width(width), height(height), outputFile(outputFile)
	{
		raw_imageBitmap = FreeImage_Allocate(width, height, bitsPerPixel);
		FreeImage_Initialise();
		logInterval = width / logFrequency;
	}

	Film::~Film() {
		FreeImage_DeInitialise();
	}
}