#include "Film.h"

namespace raytracer {

    void Film::writeToImage(const char *pngImgPathAndName) {
        BOOL isSaved = FreeImage_Save(FIF_PNG, _imageBitmap, pngImgPathAndName, PNG_DEFAULT);
        if (!isSaved) {
            printf("Error: Image not saved");
        }

    }

    Film::Film(unsigned width, unsigned height, unsigned bitsPerPixel, unsigned fragmentsPerPixel) :
            _width(width), _height(height),
            _bitsPerPixel(bitsPerPixel), _fragmentsPerPixel(fragmentsPerPixel) {
        _imageBitmap = FreeImage_Allocate(width, height, bitsPerPixel);
        FreeImage_Initialise();
    }

    Film::~Film() {
        FreeImage_DeInitialise();
    }
}