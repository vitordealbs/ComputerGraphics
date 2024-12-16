#ifndef OBJETO_H
#define OBJETO_H

#include <variant>
#include "./src/Material/Material.h"
#include "funcoes_auxiliares.h"

// Inclua os headers necessários (sem criar loops)
#include "./../Esfera/Esfera.h"
#include "./../Plano/Plano.h"
#include "./../Cilindro/Cilindro.h"
#include "./../Cone/Cone.h"
#include "./../Circulo/Circulo.h"
#include "./../Triangulo/Triangulo.h"

// Enum para os tipos de objetos
enum TipoObjeto
{
  OBJ_ESFERA,
  OBJ_PLANO,
  OBJ_CILINDRO,
  OBJ_CONE,
  OBJ_CIRCULO,
  OBJ_TRIANGULO
};

// Union
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

// Estrutura Objeto
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
