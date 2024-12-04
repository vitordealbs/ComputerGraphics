// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#define DIMENSAO_MAXIMA 4

namespace funcoes_auxiliares {
// Definição da estrutura Vetor3d
struct Vetor3d
{
  float x; // Componente x
  float y; // Componente y
  float z; // Componente z

  float dot_product(Vetor3d vetor);
  Vetor3d cross_product(Vetor3d vetor);
  float tamanho();
  Vetor3d normalizado();
  Matriz matriz();
};
// Métodos auxiliares de operação
Vetor3d
operator*(Vetor3d vetor, float escalar);
Vetor3d
operator*(float escalar, Vetor3d vetor);
Vetor3d
operator*(Vetor3d vetor1, Vetor3d vetor2);
Vetor3d
operator+(Vetor3d vetor1, Vetor3d vetor2);
Vetor3d
operator-(Vetor3d vetor1, Vetor3d vetor2);

struct Matriz
{
  int lin;
  int col;

  float data[DIMENSAO_MAXIMA][DIMENSAO_MAXIMA];

  Matriz transposta();
};

Matriz
operator+(Matriz matriz1, Matriz matriz2);

Matriz
operator-(Matriz matriz1, Matriz matriz2);

Matriz
operator*(Matriz matriz1, Matriz matriz2);

Matriz
operator*(float escalar, Matriz matriz);

Matriz
operator*(Matriz matriz, float escalar);

Matriz
operator*(Vetor3d vetor, Matriz matriz);

Matriz
operator*(Matriz matriz, Vetor3d vetor);

}

#endif // FUNCOES_AUXILIARES_H
