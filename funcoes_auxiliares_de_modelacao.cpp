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

float
Raio::intersecao(Cilindro cilindro)
{
  Vetor3d v = P0 - cilindro.centro;
  Vetor3d u = dr - dr.dot_product(cilindro.direcao) * cilindro.direcao;
  Vetor3d w = v - (v.dot_product(cilindro.direcao)) * cilindro.direcao;
  double a = u.dot_product(u);
  double b = 2 * u.dot_product(w);
  double c = w.dot_product(w) - cilindro.raio * cilindro.raio;
  double delta = b * b - 4 * a * c;
  if (delta < 0.0) {
    return -1.0f;
  }
  double t = (-b - sqrt(delta)) / (2 * a);
  if (t < 0.0) {
    t = (-b + sqrt(delta)) / (2 * a);
  }
  if (no_ponto(t).dot_product(cilindro.direcao) > cilindro.altura) {
    return -1.0f;
  }
  return t;
}

float
Raio::intersecao(Cone cone)
{
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

Plano
Plano::tres_pontos(Vetor3d P1,
                   Vetor3d P2,
                   Vetor3d P3,
                   Vetor3d K_d,
                   Vetor3d K_e,
                   Vetor3d K_a,
                   float m)
{
  Vetor3d v1 = P2 - P1;
  Vetor3d v2 = P3 - P1;
  Vetor3d w = v1.cross_product(v2);
  Vetor3d n = w.normalizado();
  return Plano(P1, n, K_d, K_e, K_a, m);
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

Cone::Cone(Vetor3d centro,
           float raio,
           float altura,
           Vetor3d direcao,
           Vetor3d K_d,
           Vetor3d K_e,
           Vetor3d K_a,
           float m)
  : centro(centro)
  , raio(raio)
  , altura(altura)
  , direcao(direcao)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}

Vetor3d
Cone::calcular_iluminacao(Vetor3d Pt,
                          Vetor3d dr,
                          Vetor3d P_F,
                          Vetor3d I_F,
                          Vetor3d I_A)
{
}

Cilindro::Cilindro(Vetor3d centro,
                   float raio,
                   float altura,
                   Vetor3d direcao,
                   Vetor3d K_d,
                   Vetor3d K_e,
                   Vetor3d K_a,
                   float m)
  : centro(centro)
  , raio(raio)
  , altura(altura)
  , direcao(direcao)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}

Vetor3d
Cilindro::calcular_iluminacao(Vetor3d Pt,
                              Vetor3d dr,
                              Vetor3d P_F,
                              Vetor3d I_F,
                              Vetor3d I_A)
{
  Vetor3d z = direcao;
  Vetor3d normal = (Pt - (Pt.dot_product(z)) * z).normalizado();
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
