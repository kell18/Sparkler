#include "CoordinateSystem.h"

namespace raytracer {

    CoordinateSystem CoordinateSystem::BuildOrthonormalBasis(vec3 _Y, vec3 _Z) {
        CoordinateSystem cs;
        cs.Z = normalize(_Z);
        cs.X = cross(_Y, cs.Z);
        cs.Y = cross(cs.Z, cs.X);
        return cs;
    }
}