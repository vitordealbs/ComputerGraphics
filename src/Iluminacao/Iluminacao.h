//
// Created by Vitor de Albuquerque on 16/12/2024.
//

#ifndef ILUMINACAO_H
#define ILUMINACAO_H
#include "./src/Raio/Raio.h"
#include "funcoes_auxiliares.h"
using namespace funcoes_auxiliares;

namespace iluminacao {

struct FontePontual
{
  Vetor3d posicao;
  Vetor3d intensidade;

  FontePontual(Vetor3d posicao, Vetor3d intensidade);

  void transformar(Matriz mat);
};

Vetor3d
modelo_phong(Vetor3d Pt,
             Vetor3d dr,
             Vetor3d n,
             FontePontual fonte,
             Vetor3d I_A,
             MaterialSimples material);
Vetor3d
luz_ambiente(Vetor3d I_A, Vetor3d K_a);

}

#endif // ILUMINACAO_H
