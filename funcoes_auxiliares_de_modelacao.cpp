// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares_de_modelacao.h"
#include "funcoes_auxiliares.h" // Incluindo as operações vetoriais
#include <cmath>                // Para pow e sqrt

using namespace funcoes_auxiliares; // Usando o namespace "Auxiliares"
using namespace Auxiliares_de_modelacao;

namespace Auxiliares_de_modelacao {

double
max(double a, double b)
{
  return a + (b - a) * (a < b);
}

double
min(double a, double b)
{
  return a + (b - a) * (a > b);
}

// Definição do construtor da Esfera
Esfera::Esfera(Vetor3d centro,
               float raio,
               Vetor3d K_d,
               Vetor3d K_e,
               Vetor3d K_a,
               float m)
  : centro(centro)
  , raio(raio)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}

Vetor3d
Esfera::calcular_iluminacao(Vetor3d Pt,
                            Vetor3d dr,
                            Vetor3d P_F,
                            Vetor3d I_F,
                            Vetor3d I_A)
{
  Vetor3d v = dr * -1;
  Vetor3d l = (P_F - Pt).normalizado();
  Vetor3d n = (Pt - centro).normalizado();
  float dotproduct_nl = n.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * n - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d I_d = K_d * I_F * max(dotproduct_nl, 0);
  Vetor3d I_e = K_e * I_F * pow(max(dotproduct_vr, 0), m);
  Vetor3d I_a = K_a * I_A;

  Vetor3d I_total = I_d + I_e + I_a;
  return I_total;
}

// Definição do construtor de Raio
Raio::Raio(Vetor3d P0, Vetor3d dr)
  : P0(P0)
  , dr(dr)
{
}

Vetor3d
Raio::no_ponto(float t)
{
  return P0 + dr * t;
}

float
Raio::intersecao(Esfera esfera)
{
  Vetor3d v = P0 - esfera.centro;
  double a = dr.dot_product(dr);
  double b = 2 * dr.dot_product(v);
  double c = v.dot_product(v) - esfera.raio * esfera.raio;
  double delta = b * b - 4 * a * c;
  if (delta < 0.0) {
    return -1.0f;
  }
  float t = (-b - sqrt(delta)) / (2 * a);
  if (t < 0.0) {
    t = (-b + sqrt(delta)) / (2 * a);
  }
  return t;
}
Plano::Plano(Vetor3d ponto,
             Vetor3d normal,
             Vetor3d K_d,
             Vetor3d K_e,
             Vetor3d K_a,
             float m)
  : ponto(ponto)
  , normal(normal)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}
float
Raio::intersecao(Plano plano)
{
  Vetor3d v = P0 - plano.ponto;
  double a = dr.dot_product(plano.normal);
  if (a == 0.0) {
    return -1.0;
  }
  double b = v.dot_product(plano.normal);
  return -b / a;
}
Vetor3d
Plano::calcular_iluminacao(Vetor3d Pt,
                           Vetor3d dr,
                           Vetor3d P_F,
                           Vetor3d I_F,
                           Vetor3d I_A)
{
  Vetor3d v = dr * -1;
  Vetor3d l = (P_F - Pt).normalizado();
  float dotproduct_nl = normal.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * normal - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d I_a = K_a * I_A;
  Vetor3d I_d = K_d * I_F * max(dotproduct_nl, 0.0);
  Vetor3d I_e = K_e * I_F * pow(max(dotproduct_vr, 0.0), m);

  Vetor3d I_total = I_d + I_e + I_a;
  return I_total;
}

}
