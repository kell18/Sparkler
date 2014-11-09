#include <stdio.h>
#include "Scene.h"

namespace raytracer {

    void Scene::render() {

        FIBITMAP* bitmap = FreeImage_Allocate(_camera->width, _camera->height, 24);

        for (unsigned i = 0, w = _camera->width; i < w; ++i) {
            for (unsigned j = 0, h = _camera->height; j < h; ++j) {
                ITracer *tracer = _camera->CreateRay(i, j);
                RGBQUAD color = vec4ToRgbaquad(tracer->trace(this, 2));
                FreeImage_SetPixelColor(bitmap, i, j, &color);
            }
        }

        FreeImage_Save(FIF_PNG, bitmap, "../resources/out.png", 0);
        printf("Image saved");
    }

    void Scene::addPrimitive(DisplayObject primitive) {
        _objects.push_back(primitive);
    }

    Scene::Scene(Camera* _camera, vector<DisplayObject>&objects, int fragmentsPerPixel) :
            _camera(_camera), _objects(objects), fragmentsPerPixel(fragmentsPerPixel) {
        FreeImage_Initialise();
    }

    Scene::~Scene() {
        FreeImage_DeInitialise();
    }

    RGBQUAD Scene::vec4ToRgbaquad(vec4 vColor) {
        RGBQUAD qColor;
        qColor.rgbRed = (BYTE) vColor[0];
        qColor.rgbGreen = (BYTE) vColor[1];
        qColor.rgbBlue = (BYTE) vColor[2];
        qColor.rgbReserved = (BYTE) vColor[3];
        return qColor;
    }
}
