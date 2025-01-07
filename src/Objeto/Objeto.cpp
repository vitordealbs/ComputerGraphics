#include "Objeto.h"
#include <cstring>

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

Objeto::Objeto(PlanoTextura plano_tex)
{
  tipo = OBJ_PLANO_TEXTURA;
  obj.plano_tex = plano_tex;

  material = {};
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
      return obj.esfera.transformar(mat);
    } break;
    case OBJ_PLANO: {
      return obj.plano.transformar(mat);
    } break;
    case OBJ_PLANO_TEXTURA: {
      return obj.plano_tex.transformar(mat);
    } break;
    case OBJ_CILINDRO: {
      return obj.cilindro.transformar(mat);
    } break;
    case OBJ_CONE: {
      return obj.cone.transformar(mat);
    } break;
    case OBJ_CIRCULO: {
      return obj.circulo.transformar(mat);
    } break;
    case OBJ_TRIANGULO: {
      return obj.triangulo.transformar(mat);
    } break;
    default: {
    } break;
  }
}