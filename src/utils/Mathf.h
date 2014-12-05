#ifndef MATHF_H
#define MATHF_H

namespace raytracer {

    class Mathf {
    public:
        static bool     isBetweenPoints(float value, float a, float b, float accuracy = 0.000001);
        static bool     isEqualWithAccuracy(float a, float b, float accuracy = 0.000001);
    };

}

#endif