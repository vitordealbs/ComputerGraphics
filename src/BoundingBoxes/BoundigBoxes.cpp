//
// Created by Vitor on 17/02/2025.
//

#include "BoundigBoxes.h"
BoundingBoxA transformBoundingBox(const BoundingBoxA& box, const Matriz& M)
{

    Vetor3d corners[8] = {
        { box.min.x, box.min.y, box.min.z },
        { box.min.x, box.min.y, box.max.z },
        { box.min.x, box.max.y, box.min.z },
        { box.min.x, box.max.y, box.max.z },
        { box.max.x, box.min.y, box.min.z },
        { box.max.x, box.min.y, box.max.z },
        { box.max.x, box.max.y, box.min.z },
        { box.max.x, box.max.y, box.max.z }
    };


    BoundingBoxA result;

    for (int i = 0; i < 8; i++) {
        Vetor3d t = (M * corners[i].ponto4d()).vetor3d();

        // Expande result
        if (t.x < result.min.x) result.min.x = t.x;
        if (t.y < result.min.y) result.min.y = t.y;
        if (t.z < result.min.z) result.min.z = t.z;

        if (t.x > result.max.x) result.max.x = t.x;
        if (t.y > result.max.y) result.max.y = t.y;
        if (t.z > result.max.z) result.max.z = t.z;
    }

    return result;
}