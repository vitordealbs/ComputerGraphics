#include "funcoes_auxiliares.h"

#ifndef Camera_H
#define Camera_H

using namespace funcoes_auxiliares;
class Camera
{
public:
    Vetor3d position;
    Vetor3d lookAt;
    Vetor3d viewUp;

    Vetor3d i{}; // Vetor horizontal
    Vetor3d j{}; // Vetor vertical
    Vetor3d k{}; // Vetor direção para trás

    Matriz transformationMatrix{};

    Camera(Vetor3d position, Vetor3d lookAt, Vetor3d viewUp);

    Matriz getTransformationMatrix();
};

#endif