//
// Created by Vitor de Albuquerque on 16/12/2024.
//

#include "Iluminacao.h"
#include <math.h>

iluminacao::FontePontual::FontePontual(Vetor3d posicao, Vetor3d intensidade)
  : posicao(posicao)
  , intensidade(intensidade)
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

void
iluminacao::FontePontual::transformar(Matriz mat)
{
  posicao = (mat * posicao.ponto4d()).vetor3d();
}
