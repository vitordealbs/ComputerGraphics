#include "Raio.h"
#include <math.h>
using namespace funcoes_auxiliares;

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
  if (a == 0.0) {
    return b == 0.0 ? -1.0f : -c / b;
  }
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
  Vetor3d r1 = triangulo.P0 - Pt;
  Vetor3d r2 = triangulo.P1 - Pt;
  Vetor3d r3 = triangulo.P2 - Pt;
  float s1 =
    r3.cross_product(r1).dot_product(triangulo.normal) / triangulo.area2;
  if (s1 < 0.0f)
    return -1.0f;
  float s2 =
    r1.cross_product(r2).dot_product(triangulo.normal) / triangulo.area2;
  if (s2 < 0.0f)
    return -1.0f;
  float s3 = 1 - s1 - s2;
  if (s3 < 0.0f)
    return -1.0f;
  return t;
}
