#ifndef RAYTRACER
#define RAYTRACER

#include "Scene.h"
#include "../geometry/primitives/Ray.h"
#include "../geometry/Collision.h"

#define SHADOW_ACCURACY 0.0001

namespace raytracer {

    class Ray;
    class Scene;
    class Light;

    class Raytracer {
    private:
        const Scene& _scene;

    public:
        vec3            trace(const Ray& ray, unsigned recursionDepth = 5, vec3 startColor = vec3(0.0f)) const;

        Ray             createReflectedRay(const Ray &directRay, const Collision &collision) const;

        Collision       findNearestCollisionTo(const Ray& ray) const;

        vec3            computeLighting(const Light& light, const Collision& collision, const Ray& ray) const;


                        Raytracer(const Scene& scene);

    private:
        bool            isInShadow(const Light& light, const Collision& collision) const;

    };

}

#endif