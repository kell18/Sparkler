#include "Primitive.h"

namespace raytracer {

//    Primitive& Primitive::operator =(const Primitive &copiedPrimitive) {
//        if (this == &copiedPrimitive) {
//            return *this;
//        }
//        position = copiedPrimitive.position;
//        transforms = copiedPrimitive.transforms;
//        material = *(copiedPrimitive.material.clone());
//        return *this;
//    }
//
//    Primitive::Primitive(const Primitive &copiedPrimitive) {
//        position = copiedPrimitive.position;
//        transforms = copiedPrimitive.transforms;
//        material = *(copiedPrimitive.material.clone());
//    }
//
//    Primitive::Primitive() {
//    }

    Primitive::~Primitive() {
    }

}