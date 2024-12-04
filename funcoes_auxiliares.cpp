// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares.h"
#include <cassert>
#include <cmath> // Para sqrtf()

namespace funcoes_auxiliares {

float
Vetor3d::dot_product(Vetor3d vetor)
{
  return x * vetor.x + y * vetor.y + z * vetor.z;
}

Vetor3d
Vetor3d::cross_product(Vetor3d vetor)
{
  Vetor3d resultado = { y * vetor.z - z * vetor.y,
                        z * vetor.x - x * vetor.z,
                        x * vetor.y - y * vetor.x };
  return resultado;
}

float
Vetor3d::tamanho()
{
  return sqrtf(x * x + y * y + z * z);
}

Vetor3d
Vetor3d::normalizado()
{
  float tam = tamanho();
  Vetor3d resultado = { x / tam, y / tam, z / tam };
  return resultado;
}

Matriz
Vetor3d::matriz()
{
  Matriz res = { .lin = 3, .col = 1 };
  res.data[0][0] = x;
  res.data[1][0] = y;
  res.data[2][0] = z;
  return res;
}

Vetor3d
operator*(Vetor3d vetor, float escalar)
{
  Vetor3d resultado = { vetor.x * escalar,
                        vetor.y * escalar,
                        vetor.z * escalar };
  return resultado;
}

Vetor3d
operator*(float escalar, Vetor3d vetor)
{
  Vetor3d resultado = { vetor.x * escalar,
                        vetor.y * escalar,
                        vetor.z * escalar };
  return resultado;
}

Vetor3d
operator*(Vetor3d vetor1, Vetor3d vetor2)
{
  Vetor3d resultado = { vetor1.x * vetor2.x,
                        vetor1.y * vetor2.y,
                        vetor1.z * vetor2.z };
  return resultado;
}

Vetor3d
operator+(Vetor3d vetor1, Vetor3d vetor2)
{
  Vetor3d resultado = { vetor1.x + vetor2.x,
                        vetor1.y + vetor2.y,
                        vetor1.z + vetor2.z };
  return resultado;
}

Vetor3d
operator-(Vetor3d vetor1, Vetor3d vetor2)
{
  Vetor3d resultado = { vetor1.x - vetor2.x,
                        vetor1.y - vetor2.y,
                        vetor1.z - vetor2.z };
  return resultado;
}

Matriz
Matriz::transposta()
{
  Matriz res = { .lin = col, .col = lin };
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; ++j) {
      res.data[j][i] = data[i][j];
    }
  }
  return res;
}

Matriz
operator+(Matriz matriz1, Matriz matriz2)
{
  assert(matriz1.lin == matriz2.lin && matriz1.col == matriz2.col);
  Matriz res = { .lin = matriz1.lin, .col = matriz1.col };
  for (int i = 0; i < res.lin; ++i) {
    for (int j = 0; j < res.col; ++j) {
      res.data[i][j] = matriz1.data[i][j] + matriz2.data[i][j];
    }
  }
  return res;
}

Matriz
operator-(Matriz matriz1, Matriz matriz2)
{
  assert(matriz1.lin == matriz2.lin && matriz1.col == matriz2.col);
  Matriz res = { .lin = matriz1.lin, .col = matriz1.col };
  for (int i = 0; i < res.lin; ++i) {
    for (int j = 0; j < res.col; ++j) {
      res.data[i][j] = matriz1.data[i][j] - matriz2.data[i][j];
    }
  }
  return res;
}

Matriz
operator*(Matriz matriz1, Matriz matriz2)
{
  assert(matriz1.col == matriz2.lin);
  Matriz res = { .lin = matriz1.lin, .col = matriz2.col, .data = { 0 } };
  for (int i = 0; i < res.lin; ++i) {
    for (int j = 0; j < res.col; ++j) {
      for (int k = 0; k < matriz1.col; ++k) {
        res.data[i][j] += matriz1.data[i][k] * matriz2.data[k][j];
      }
    }
  }
  return res;
}

Matriz
operator*(float escalar, Matriz matriz)
{
  Matriz res = { .lin = matriz.lin, .col = matriz.col };
  for (int i = 0; i < res.lin; ++i) {
    for (int j = 0; j < res.col; ++j) {
      res.data[i][j] = escalar * matriz.data[i][j];
    }
  }
  return res;
}

Matriz
operator*(Matriz matriz, float escalar)
{
  return escalar * matriz;
}

}
