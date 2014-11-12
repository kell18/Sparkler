#include "Film.h"

namespace raytracer {

    void Film::writeToImage(const char *pngImgPathAndName) {
        BOOL isSaved = FreeImage_Save(FIF_PNG, imageBitmap, pngImgPathAndName, PNG_DEFAULT);
        if (!isSaved) {
            printf("Error: Image not saved");
        }

    }

    Film::Film(unsigned width, unsigned height, unsigned bitsPerPixel, unsigned fragmentsPerPixel) :
            width(width), height(height), bpp(bitsPerPixel), fpp(fragmentsPerPixel) {
        imageBitmap = FreeImage_Allocate(width, height, bpp);
        FreeImage_Initialise();
    }

    Film::~Film() {

        FreeImage_DeInitialise();
    }
}