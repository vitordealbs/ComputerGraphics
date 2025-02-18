#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <cfloat>

#include "funcoes_auxiliares.h"

using namespace funcoes_auxiliares;
struct BoundingBoxA {
    Vetor3d min;
    Vetor3d max;
    void expand(const Vetor3d& p) {
        if (p.x < min.x) min.x = p.x;
        if (p.y < min.y) min.y = p.y;
        if (p.z < min.z) min.z = p.z;

        if (p.x > max.x) max.x = p.x;
        if (p.y > max.y) max.y = p.y;
        if (p.z > max.z) max.z = p.z;
    }
    void expand(const BoundingBoxA& other) {
        if (other.min.x < min.x) min.x = other.min.x;
        if (other.min.y < min.y) min.y = other.min.y;
        if (other.min.z < min.z) min.z = other.min.z;

        if (other.max.x > max.x) max.x = other.max.x;
        if (other.max.y > max.y) max.y = other.max.y;
        if (other.max.z > max.z) max.z = other.max.z;
    }
};


#endif