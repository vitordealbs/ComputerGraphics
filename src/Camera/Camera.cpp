
#include "Camera3de.h"
using namespace funcoes_auxiliares;

Camera3de::Camera3de(Vetor3d position, Vetor3d lookAt, Vetor3d Up)
  : position(position)
  , lookAt(lookAt)
  , Up(Up)
{
  updateCoordinates();
}

void
Camera3de::updateCoordinates()
{
  // Calcula o vetor k (direção para trás)
  k = (position - lookAt).normalizado();

  // Calcula o vetor i (horizontal)
  Vetor3d viewUp = Up - position;
  i = viewUp.cross_product(k).normalizado();

  // Calcula o vetor j (vertical)
  j = k.cross_product(i);
}

Matriz
Camera3de::getTransformationMatrix()
{
  Matriz viewMatrix = Matriz::identidade(4);

  // Preenche a matriz com os vetores i, j, k e a posição da câmera
  viewMatrix.data[0][0] = i.x;
  viewMatrix.data[0][1] = i.y;
  viewMatrix.data[0][2] = i.z;
  viewMatrix.data[0][3] = -i.dot_product(position);

  viewMatrix.data[1][0] = j.x;
  viewMatrix.data[1][1] = j.y;
  viewMatrix.data[1][2] = j.z;
  viewMatrix.data[1][3] = -j.dot_product(position);

  viewMatrix.data[2][0] = k.x;
  viewMatrix.data[2][1] = k.y;
  viewMatrix.data[2][2] = k.z;
  viewMatrix.data[2][3] = -k.dot_product(position);

  return viewMatrix;
}

Matriz
Camera3de::getMatrixCameraWorld()
{
  Matriz viewMatrix = Matriz::identidade(4);

  // Preenche a matriz com os vetores i, j, k e a posição da câmera
  viewMatrix.data[0][0] = i.x;
  viewMatrix.data[0][1] = j.x;
  viewMatrix.data[0][2] = k.x;
  viewMatrix.data[0][3] = position.x;

  viewMatrix.data[1][0] = i.y;
  viewMatrix.data[1][1] = j.y;
  viewMatrix.data[1][2] = k.y;
  viewMatrix.data[1][3] = position.y;

  viewMatrix.data[2][0] = i.z;
  viewMatrix.data[2][1] = j.z;
  viewMatrix.data[2][2] = k.z;
  viewMatrix.data[2][3] = position.z;

  return viewMatrix;
}