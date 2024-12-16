//
// Created by Vitor de Albuquerque on 16/12/2024.
//

#include "Triangulo.h"

Triangulo::Triangulo(Vetor3d P0,
                     Vetor3d P1,
                     Vetor3d P2,
                     Vetor3d K_d,
                     Vetor3d K_e,
                     Vetor3d K_a,
                     float m)
  : P0(P0)
  , P1(P1)
  , P2(P2)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
    lado1 = P1 - P0;
    lado2 = P2 - P0;
    lado3 = P2 - P1;
    Vetor3d N = lado1.cross_product(lado2);
    area2 = N.tamanho();
    normal = N * (1.0f / area2);
}