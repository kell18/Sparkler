#include "Film.h"

namespace raytracer {

    void Film::commitFragment(unsigned x, unsigned y, vec4 color) {
        if (color.r > _maxBrightness.r) {
            _maxBrightness.r = color.r;
        }
        if (color.g > _maxBrightness.g) {
            _maxBrightness.g = color.g;
        }
        if (color.b > _maxBrightness.b) {
            _maxBrightness.b = color.b;
        }
        _imageFragments[x * _height + y] = color;
    };

    void Film::writeToImage(const char *pngImgPathAndName) {
        computeImageBitmap();
        BOOL isSaved = FreeImage_Save(FIF_PNG, _imageBitmap, pngImgPathAndName, PNG_DEFAULT);
        if (!isSaved) {
            printf("Error: Image not saved");
        }
    }

    void Film::computeImageBitmap() {
        for (unsigned i = 0; i < _width; ++i) {
            for (unsigned j = 0; j < _height; ++j) {
                RGBQUAD rgbquad = rearrangeFragment(i, j);
                FreeImage_SetPixelColor(_imageBitmap, i, j, &rgbquad);
            }
        }
    }

    inline RGBQUAD Film::rearrangeFragment(unsigned i, unsigned j) {
        RGBQUAD rgbaquad;
        rgbaquad.rgbRed = _imageFragments[i * _height + j].r / _maxBrightness.r * 255;
        rgbaquad.rgbGreen = _imageFragments[i * _height + j].g / _maxBrightness.g * 255;
        rgbaquad.rgbBlue = _imageFragments[i * _height + j].b / _maxBrightness.b * 255;
        return rgbaquad;
    }

    Film::Film(unsigned width, unsigned height, vec4 maxBrightness, unsigned bitsPerPixel, unsigned fragmentsPerPixel) :
            _width(width), _height(height), _maxBrightness(maxBrightness),
            _bitsPerPixel(bitsPerPixel), _fragmentsPerPixel(fragmentsPerPixel) {
        _imageBitmap = FreeImage_Allocate(width, height, bitsPerPixel);
        _imageFragments.reserve(width * height);
        FreeImage_Initialise();
    }

    Film::~Film() {
        FreeImage_DeInitialise();
    }
}