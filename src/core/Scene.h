#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include <glm/vec3.hpp>
#include "DisplayObject.h"
#include "Camera.h"

using namespace std;
using namespace glm;

namespace raytracer {

    class Camera;

    class Scene{
    private:
        int fragmentsPerPixel;
        Camera* _camera;
        vector<DisplayObject> _objects;
    public:
        void            addPrimitive(DisplayObject primitive);
        void            render();
                        Scene(Camera* camera, vector<DisplayObject>& objects, int fragmentsPerPixel);
                        ~Scene();

    private:
        RGBQUAD vec4ToRgbaquad(vec4 vColor);
    };

}

#endif