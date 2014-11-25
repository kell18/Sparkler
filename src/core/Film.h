#ifndef FILM_H
#define FILM_H

#include <glm/vec4.hpp>
#include <FreeImage.h>
#include <stdio.h>

using namespace glm;

namespace raytracer {

    class Film {
    private:
        unsigned _width, _height;
        unsigned _bitsPerPixel, _fragmentsPerPixel;
        FIBITMAP* _imageBitmap;

    public:
        void            writeToImage(const char* pngImgPathAndName);

        inline void     commitFragment(unsigned x, unsigned y, const vec4& color) {
            RGBQUAD rgbaquad = vec4ToRgbaquad(color);
            FreeImage_SetPixelColor(_imageBitmap, x, y, &rgbaquad);
        };

                        Film(unsigned width, unsigned height, unsigned bitsPerPixel, unsigned fragmentsPerPixel);
                        ~Film();
    private:
        inline RGBQUAD vec4ToRgbaquad(const vec4& vColor) {
            RGBQUAD qColor;
            qColor.rgbRed = (BYTE) vColor.r;
            qColor.rgbGreen = (BYTE) vColor.g;
            qColor.rgbBlue = (BYTE) vColor.b;
            qColor.rgbReserved = (BYTE) vColor.a;
            return qColor;
        }
    };

}

#endif