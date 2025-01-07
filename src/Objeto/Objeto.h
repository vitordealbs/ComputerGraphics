#ifndef OBJETO_H
#define OBJETO_H

#include "./src/Material/Material.h"
#include "funcoes_auxiliares.h"
#include <variant>

// Inclua os headers necessários (sem criar loops)
#include "./../Cilindro/Cilindro.h"
#include "./../Circulo/Circulo.h"
#include "./../Cone/Cone.h"
#include "./../Esfera/Esfera.h"
#include "./../ObjetoComplexo/ObjetoComplexo.h"
#include "./../Plano/Plano.h"
#include "./../PlanoTextura/PlanoTextura.h"
#include "./../Triangulo/Triangulo.h"

// Enum para os tipos de objetos
enum TipoObjeto
{
  OBJ_ESFERA,
  OBJ_PLANO,
  OBJ_PLANO_TEXTURA,
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
  PlanoTextura plano_tex;
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
  Objeto(PlanoTextura plano_tex);
  Objeto(Cilindro cilindro);
  Objeto(Cone cone);
  Objeto(Circulo circulo);
  Objeto(Triangulo triangulo);

  Vetor3d normal(Vetor3d Pt);
  void transformar(Matriz mat);
};

#endif // OBJETO_H
