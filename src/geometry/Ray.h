#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <glm/vec4.hpp>
#include "../core/Camera.h"
#include "../core/Scene.h"

namespace raytracer {

    class Camera;
    class Scene;

    class Ray {
    private:
        Camera* _cam;
        
    public:
        vec4 eye, direction;
        int x, y;


        vec4*           trace(Scene* scene, int depth) ;
                        Ray(int x, int y, Camera* camera);
    };

}

#endif