#include "funcoes_auxiliares.h"

#ifndef Camera_H
#define Camera_H

using namespace funcoes_auxiliares;
class Camera3de
{
public:
  Vetor3d position;
  Vetor3d lookAt;
  Vetor3d Up;

  Vetor3d i{}; // Vetor horizontal
  Vetor3d j{}; // Vetor vertical
  Vetor3d k{}; // Vetor direção para trás

  Camera3de(Vetor3d position, Vetor3d lookAt, Vetor3d Up);

  void updateCoordinates();

  Matriz getTransformationMatrix();
  Matriz getMatrixCameraWorld();
};

#endif