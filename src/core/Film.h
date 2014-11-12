#ifndef FILM_H
#define FILM_H

#include <glm/vec4.hpp>
#include <FreeImage.h>
#include <stdio.h>

using namespace glm;

namespace raytracer {

    class Film {
    private:
        unsigned width, height;
        // BitsPerPixel and FragmentsPerPixel
        unsigned bpp, fpp;
        FIBITMAP* imageBitmap;

    public:
        void            writeToImage(const char*pngImgPathAndName);

        inline void     commitFragment(unsigned x, unsigned y, vec4 *color) {
            FreeImage_SetPixelColor(imageBitmap, x, y, vec4ToRgbaquad(color));
        };
                        Film(unsigned width, unsigned height, unsigned bitsPerPixel, unsigned fragmentsPerPixel);
                        ~Film();
    private:
        inline RGBQUAD* vec4ToRgbaquad(vec4* vColor) {
            RGBQUAD *qColor = new RGBQUAD;
            qColor->rgbRed = (BYTE) vColor->r;
            qColor->rgbGreen = (BYTE) vColor->g;
            qColor->rgbBlue = (BYTE) vColor->b;
            qColor->rgbReserved = (BYTE) vColor->a;
            return qColor;
        }
    };

}

#endif