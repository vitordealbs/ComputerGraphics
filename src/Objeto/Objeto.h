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
#include "./../Malha/Malha.h"
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
  OBJ_TRIANGULO,
  OBJ_MALHA
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
  Malha malha;

  UnionObjeto();
  ~UnionObjeto();
  UnionObjeto(const UnionObjeto& objeto);
};

// Estrutura Objeto
struct Objeto
{
  TipoObjeto tipo;
  UnionObjeto obj;
  MaterialSimples material;

  Objeto(const Esfera& esfera);
  Objeto(const Plano& plano);
  Objeto(const PlanoTextura& plano_tex);
  Objeto(const Cilindro& cilindro);
  Objeto(const Cone& cone);
  Objeto(const Circulo& circulo);
  Objeto(const Triangulo& triangulo);
  Objeto(const Malha& malha);

  Vetor3d normal(Vetor3d Pt);
  void transformar(Matriz mat);
};

#endif // OBJETO_H
