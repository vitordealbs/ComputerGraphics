#ifndef RAIO_H
#define RAIO_H

#include "./../Objeto/Objeto.h"
#include <vector>
#include "funcoes_auxiliares.h"
#include "./../Objeto/Objeto.h"
#include "./../Esfera/Esfera.h"
#include "./../Plano/Plano.h"
#include "./../Cone/Cone.h"
#include "./../Cilindro/Cilindro.h"
#include "./../Circulo/Circulo.h"
#include "./../Triangulo/Triangulo.h"
using namespace funcoes_auxiliares;
class Objeto; // Declaração antecipada


struct Raio
{
  Vetor3d P0;
  Vetor3d dr;

  Raio(Vetor3d P0, Vetor3d dr);
  Vetor3d no_ponto(float t);
  float intersecao(Objeto objeto);
  float intersecao(Esfera esfera);
  float intersecao(Plano plano); // Função de intersecção com Plano
  float intersecao(Cone cone);
  float intersecao(Cilindro cilindro);
  float intersecao(Circulo circulo);
  float intersecao(Triangulo triangulo);
};

struct FontePontual
{
  Vetor3d posicao;
  Vetor3d intensidade;

  FontePontual(Vetor3d posicao, Vetor3d intensidade);
};
// calculo do material para calcular iluminação

#endif // RAIO_H
