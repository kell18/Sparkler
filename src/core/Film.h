#ifndef FILM_H
#define FILM_H

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <FreeImage.h>
#include <stdio.h>
#include <vector>

using namespace glm;
using namespace std;

namespace raytracer {

    class Film {
    private:
        unsigned _width, _height;
        unsigned _bitsPerPixel, _fragmentsPerPixel;
        vector<vec4> _imageFragments;
        FIBITMAP* _imageBitmap;
        vec4 _maxBrightness;

    public:
        void                commitFragment(unsigned x, unsigned y, vec4 color);

        void                writeToImage(const char* pngImgPathAndName);

                            Film(unsigned width, unsigned height,
                                    vec4 maxBrightness = vec4(255.0f, 255.0f, 255.0f, 1.0f),
                                    unsigned bitsPerPixel = 24, unsigned fragmentsPerPixel = 1);

                            ~Film();
    private:
        void                computeImageBitmap();

        RGBQUAD             rearrangeFragment(unsigned i, unsigned j);
    };

}

#endif