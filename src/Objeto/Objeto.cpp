#include "Objeto.h"
#include <cstring>

UnionObjeto::UnionObjeto()
{
  memset(this, 0, sizeof(UnionObjeto));
}

UnionObjeto::~UnionObjeto() {}

Objeto::Objeto(const Esfera& esfera)
{
  tipo = OBJ_ESFERA;
  obj.esfera = esfera;

  material = MaterialSimples(esfera.K_d, esfera.K_e, esfera.K_a, esfera.m);
}

Objeto::Objeto(const Plano& plano)
{
  tipo = OBJ_PLANO;
  obj.plano = plano;

  material = MaterialSimples(plano.K_d, plano.K_e, plano.K_a, plano.m);
}

Objeto::Objeto(const PlanoTextura& plano_tex)
{
  tipo = OBJ_PLANO_TEXTURA;
  obj.plano_tex = plano_tex;

  material = {};
}

Objeto::Objeto(const Cilindro& cilindro)
{
  tipo = OBJ_CILINDRO;
  obj.cilindro = cilindro;

  material =
    MaterialSimples(cilindro.K_d, cilindro.K_e, cilindro.K_a, cilindro.m);
}

Objeto::Objeto(const Cone& cone)
{
  tipo = OBJ_CONE;
  obj.cone = cone;

  material = MaterialSimples(cone.K_d, cone.K_e, cone.K_a, cone.m);
}

Objeto::Objeto(const Circulo& circulo)
{
  tipo = OBJ_CIRCULO;
  obj.circulo = circulo;

  material = MaterialSimples(circulo.K_d, circulo.K_e, circulo.K_a, circulo.m);
}

Objeto::Objeto(const Triangulo& triangulo)
{
  tipo = OBJ_TRIANGULO;
  obj.triangulo = triangulo;

  material =
    MaterialSimples(triangulo.K_d, triangulo.K_e, triangulo.K_a, triangulo.m);
}

Objeto::Objeto(const Malha& malha)
{
  tipo = OBJ_MALHA;
  obj.malha = malha;

  material = malha.material;
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
    case OBJ_PLANO_TEXTURA: {
      return obj.plano_tex.normal;
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

void
Objeto::transformar(Matriz mat)
{
  switch (tipo) {
    case OBJ_ESFERA: {
      obj.esfera.transformar(mat);
    } break;
    case OBJ_PLANO: {
      obj.plano.transformar(mat);
    } break;
    case OBJ_PLANO_TEXTURA: {
      obj.plano_tex.transformar(mat);
    } break;
    case OBJ_CILINDRO: {
      obj.cilindro.transformar(mat);
    } break;
    case OBJ_CONE: {
      obj.cone.transformar(mat);
    } break;
    case OBJ_CIRCULO: {
      obj.circulo.transformar(mat);
    } break;
    case OBJ_TRIANGULO: {
      obj.triangulo.transformar(mat);
    } break;
    case OBJ_MALHA: {
      obj.malha.transformar(mat);
    }
    default: {
    } break;
  }
}