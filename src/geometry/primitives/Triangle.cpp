#include "Triangle.h"

#define EPSILON 0.000001

namespace raytracer {

    // TODO: Move in separate class
    bool isBetweenPoints(float value, float a, float b) {
        float relativeVal = value - a;
        float length = b - a;
        return relativeVal > -EPSILON && relativeVal < length + EPSILON;
    }

    Collision Triangle::computeCollisionWith(Ray const &ray) {
        Collision collision;

        // vec4 homogenNormal = vec4(normal, 0.0f); // add dot(-normal, vertices[0]) instead 0
        float denominator = dot(normal, ray.direction); // swap the order

        if ((isBetweenPoints(denominator, -EPSILON, +EPSILON))) {
            return collision;
        }

        // TODO: Bound t with ray.tMax & ray.tMin
        float t = (dot(vertices[0], normal) - dot(ray.eye, normal)) / denominator; // change side1x2 to vertex1
        if (t < 0) {
            return collision;
        }

        collision.point = ray.eye + ray.direction * t;
        collision.normal = normal;

        vec3 T = collision.point - vertices[0];
        vec3 E1 = side1x2;
        vec3 E2 = side1x3;
        vec3 P = cross(ray.direction, E2);
        vec3 Q = cross(collision.point, E1);

        float coef = pow(dot(P, E1), -1.0f);
        float alpha = coef * dot(Q, E2);
        float beta = coef * dot(P, collision.point);
        float gamma = coef * dot(Q, ray.direction);

//            vec3 Q1xQ2neg = -Q1 * Q2;

//            auto coef = (Q1 * Q1 * Q2 * Q2 - (Q1xQ2neg * Q1xQ2neg), vec3(-1.0f));

//            float beta = coef * Q2 * Q2 * R * Q1 + Q1xQ2neg * R * Q2;
//            float gamma = coef * Q1xQ2neg * R * Q1 + Q1 * Q1 * R * Q2;
//            float alpha = 1.0f - beta - gamma;



        collision.isFind = isBetweenPoints(alpha, 0.0f, 1.0f) &&
                           isBetweenPoints(beta, 0.0f, 1.0f) &&
                           isBetweenPoints(gamma, 0.0f, 1.0f) &&
                           (alpha + beta + gamma) < 1.0f + EPSILON;

//            vec3 v3point = vec3(collision.point);
//            collision.isFind = dot(cross(vertices[1] - vertices[0], v3point - vertices[0]), normal) >= -EPSILON &&
//                               dot(cross(vertices[2] - vertices[1], v3point - vertices[1]), normal) >= -EPSILON &&
//                               dot(cross(vertices[0] - vertices[2], v3point - vertices[2]), normal) >= -EPSILON;

        return collision;
    }

    Triangle::Triangle(Material material, vec3 vertices[3], mat4 transforms)
            : Primitive(vertices[0], material, transforms) {
        this->vertices[0] = vertices[0];
        this->vertices[1] = vertices[1];
        this->vertices[2] = vertices[2];
        side1x2 = vertices[1] - vertices[0];
        side1x3 = vertices[2] - vertices[0];
        // TODO: Incorrect behaviour with normalize normalize
        normal = normalize(cross(side1x2, side1x3));
    }

    Triangle::~Triangle() {
    }
}