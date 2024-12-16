#ifndef OBJETO_H
#define OBJETO_H
#include <variant>
#include "./src/Material/Material.h"
#include "funcoes_auxiliares.h"
#include "./../Esfera/Esfera.h"
#include "./../Plano/Plano.h"
#include "./../Cone/Cone.h"
#include "./../Cilindro/Cilindro.h"
#include "./../Circulo/Circulo.h"
#include "./../Triangulo/Triangulo.h"





enum TipoObjeto
{
  OBJ_ESFERA,
  OBJ_PLANO,
  OBJ_CILINDRO,
  OBJ_CONE,
  OBJ_CIRCULO,
  OBJ_TRIANGULO
};

union UnionObjeto
{
  Esfera esfera;
  Plano plano;
  Cilindro cilindro;
  Cone cone;
  Circulo circulo;
  Triangulo triangulo;

  UnionObjeto();
};

struct Objeto
{
  TipoObjeto tipo;
  UnionObjeto obj;

  MaterialSimples material;

  Objeto(Esfera esfera);
  Objeto(Plano plano);
  Objeto(Cilindro cilindro);
  Objeto(Cone cone);
  Objeto(Circulo circulo);
  Objeto(Triangulo triangulo);

  Vetor3d normal(Vetor3d Pt);
};

#endif // OBJETO_H
