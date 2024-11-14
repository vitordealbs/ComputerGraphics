// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares_de_modelacao.h"
#include "funcoes_auxiliares.h" // Incluindo as operações vetoriais
#include <cmath>                // Para pow e sqrt
#include <cstring>              // Para memset

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

Vetor3d
Esfera::normal(Vetor3d Pt)
{
  return (Pt - centro).normalizado();
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
Raio::intersecao(Objeto objeto)
{
  switch (objeto.tipo) {
    case OBJ_ESFERA: {
      return intersecao(objeto.obj.esfera);
    } break;
    case OBJ_PLANO: {
      return intersecao(objeto.obj.plano);
    } break;
    case OBJ_CILINDRO: {
      return intersecao(objeto.obj.cilindro);
    } break;
    case OBJ_CONE: {
      return intersecao(objeto.obj.cone);
    } break;
    case OBJ_CIRCULO: {
      return intersecao(objeto.obj.circulo);
    } break;
    case OBJ_TRIANGULO: {
      return intersecao(objeto.obj.triangulo);
    } break;
    default: {
      return -1.0f;
    } break;
  }
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
  float altura_t =
    (no_ponto(t) - cilindro.centro).dot_product(cilindro.direcao);
  if (t < 0.0 || altura_t > cilindro.altura || altura_t < 0.0f) {
    t = (-b + sqrt(delta)) / (2 * a);
    altura_t = (no_ponto(t) - cilindro.centro).dot_product(cilindro.direcao);
  }
  if (altura_t > cilindro.altura || altura_t < 0.0f) {
    return -1.0f;
  }
  return t;
}

float
Raio::intersecao(Cone cone)
{
  float R = cone.raio;
  float h = cone.altura;
  float fator = R * R / (h * h);
  Vetor3d z = cone.direcao;
  Vetor3d v = P0 - (cone.centro + z * h);
  Vetor3d u = dr - dr.dot_product(z) * z;
  Vetor3d w = v - (v.dot_product(z)) * z;
  double a1 = u.dot_product(u);
  double b1 = 2 * u.dot_product(w);
  double c1 = w.dot_product(w);
  double a2 = pow(dr.dot_product(z), 2.0) * fator;
  double b2 = 2 * dr.dot_product(z) * (v.dot_product(z)) * fator;
  double c2 = pow(v.dot_product(z), 2.0) * fator;
  double a = a1 - a2;
  double b = b1 - b2;
  double c = c1 - c2;
  double delta = b * b - 4 * a * c;
  if (delta < 0.0) {
    return -1.0f;
  }
  double t = (-b - sqrt(delta)) / (2 * a);
  double menor_t = t;
  float altura_t = (no_ponto(menor_t) - cone.centro).dot_product(z);
  if ((t = (-b + sqrt(delta)) / (2 * a)) > 0.0 &&
      (menor_t < 0.0 || t < menor_t || altura_t > h || altura_t < 0.0f)) {
    menor_t = t;
    altura_t = (no_ponto(menor_t) - cone.centro).dot_product(z);
  }
  if (altura_t > h || altura_t < 0.0f) {
    return -1.0f;
  }
  return menor_t;
}

float
Raio::intersecao(Circulo circulo)
{
  Vetor3d v = P0 - circulo.centro;
  double a = dr.dot_product(circulo.normal);
  if (a == 0.0) {
    return -1.0f;
  }
  double b = v.dot_product(circulo.normal);
  double t = -b / a;
  Vetor3d Pt = no_ponto(t);
  if ((Pt - circulo.centro).tamanho() > circulo.raio) {
    return -1.0f;
  }
  return t;
}

float
Raio::intersecao(Triangulo triangulo)
{
  Vetor3d v = P0 - triangulo.P0;
  double a = dr.dot_product(triangulo.normal);
  if (a == 0.0) {
    return -1.0f;
  }
  double b = v.dot_product(triangulo.normal);
  double t = -b / a;
  Vetor3d Pt = no_ponto(t);
  Vetor3d w = Pt - triangulo.P0;
  Vetor3d u = Pt - triangulo.P1;
  if (triangulo.altura1.dot_product(w) < 0.0f ||
      triangulo.altura2.dot_product(w) < 0.0f ||
      triangulo.altura3.dot_product(u) < 0.0f) {
    return -1.0f;
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
  Vetor3d z = direcao;
  Vetor3d centro_Pt = Pt - centro;
  Vetor3d normal = (centro_Pt - (centro_Pt.dot_product(z)) * z).normalizado();
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

Vetor3d
Cone::normal(Vetor3d Pt)
{
  Vetor3d z = direcao;
  Vetor3d centro_Pt = Pt - centro;
  return (centro_Pt - centro_Pt.dot_product(z) * z).normalizado();
}

Circulo::Circulo(Vetor3d centro,
                 float raio,
                 Vetor3d normal,
                 Vetor3d K_d,
                 Vetor3d K_e,
                 Vetor3d K_a,
                 float m)
  : centro(centro)
  , raio(raio)
  , normal(normal)
  , K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}

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
  altura1 = lado2 - lado1.normalizado() * lado2.dot_product(lado1) *
                      (1.0f / lado1.tamanho());
  altura2 = lado1 - lado2.normalizado() * lado1.dot_product(lado2) *
                      (1.0f / lado2.tamanho());
  altura3 =
    lado3.normalizado() * lado3.dot_product(lado1) * (1.0f / lado3.tamanho()) -
    lado1;
  normal = lado1.cross_product(lado2).normalizado();
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
  Vetor3d centro_Pt = Pt - centro;
  Vetor3d normal = (centro_Pt - centro_Pt.dot_product(z) * z).normalizado();
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

Vetor3d
Cilindro::normal(Vetor3d Pt)
{
  Vetor3d z = direcao;
  Vetor3d centro_Pt = Pt - centro;
  return (centro_Pt - centro_Pt.dot_product(z) * z).normalizado();
}

UnionObjeto::UnionObjeto()
{
  memset(this, 0, sizeof(UnionObjeto));
}

Objeto::Objeto(Esfera esfera)
{
  tipo = OBJ_ESFERA;
  obj.esfera = esfera;

  material = MaterialSimples(esfera.K_d, esfera.K_e, esfera.K_a, esfera.m);
}

Objeto::Objeto(Plano plano)
{
  tipo = OBJ_PLANO;
  obj.plano = plano;

  material = MaterialSimples(plano.K_d, plano.K_e, plano.K_a, plano.m);
}

Objeto::Objeto(Cilindro cilindro)
{
  tipo = OBJ_CILINDRO;
  obj.cilindro = cilindro;

  material =
    MaterialSimples(cilindro.K_d, cilindro.K_e, cilindro.K_a, cilindro.m);
}

Objeto::Objeto(Cone cone)
{
  tipo = OBJ_CONE;
  obj.cone = cone;

  material = MaterialSimples(cone.K_d, cone.K_e, cone.K_a, cone.m);
}

Objeto::Objeto(Circulo circulo)
{
  tipo = OBJ_CIRCULO;
  obj.circulo = circulo;

  material = MaterialSimples(circulo.K_d, circulo.K_e, circulo.K_a, circulo.m);
}

Objeto::Objeto(Triangulo triangulo)
{
  tipo = OBJ_TRIANGULO;
  obj.triangulo = triangulo;

  material =
    MaterialSimples(triangulo.K_d, triangulo.K_e, triangulo.K_a, triangulo.m);
}

Vetor3d
Objeto::normal(Vetor3d Pt)
{
  switch (tipo) {
    case OBJ_ESFERA: {
      return obj.esfera.normal(Pt);
    } break;
    case OBJ_PLANO: {
      return obj.plano.normal;
    } break;
    case OBJ_CILINDRO: {
      return obj.cilindro.normal(Pt);
    } break;
    case OBJ_CONE: {
      return obj.cone.normal(Pt);
    } break;
    case OBJ_CIRCULO: {
      return obj.circulo.normal;
    } break;
    case OBJ_TRIANGULO: {
      return obj.triangulo.normal;
    } break;
    default: {
      return { 0.0f, 0.0f, 0.0f };
    } break;
  }
}

FontePontual::FontePontual(Vetor3d posicao, Vetor3d intensidade)
  : posicao(posicao)
  , intensidade(intensidade)
{
}

MaterialSimples::MaterialSimples(Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m)
  : K_d(K_d)
  , K_e(K_e)
  , K_a(K_a)
  , m(m)
{
}

Vetor3d
iluminacao::modelo_phong(Vetor3d Pt,
                         Vetor3d dr,
                         Vetor3d n,
                         FontePontual fonte,
                         Vetor3d I_A,
                         MaterialSimples material)
{
  Vetor3d v = dr * -1;
  Vetor3d l = (fonte.posicao - Pt).normalizado();
  float dotproduct_nl = n.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * n - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d E_a = material.K_a * I_A;
  Vetor3d E_d = material.K_d * fonte.intensidade * max(dotproduct_nl, 0.0);
  Vetor3d E_e =
    material.K_e * fonte.intensidade * pow(max(dotproduct_vr, 0.0), material.m);

  Vetor3d E_total = E_d + E_e + E_a;
  return E_total;
}

Vetor3d
iluminacao::luz_ambiente(Vetor3d I_A, Vetor3d K_a)
{
  return K_a * I_A;
}

}
