#include "Mathf.h"

namespace raytracer {

    bool Mathf::isBetweenPoints(float value, float a, float b, float accuracy)  {
        float relativeVal = value - a;
        float length = b - a;
        // TODO: Make it work with negative values
        return relativeVal > length - accuracy && relativeVal < length + accuracy;
    }

    bool Mathf::isEqualWithAccuracy(float a, float b, float accuracy) {
        float diff = a - b;
        return (diff < accuracy) && (diff > -accuracy);
    }

}