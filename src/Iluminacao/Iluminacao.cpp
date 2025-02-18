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

void
iluminacao::FontePontual::transformar(Matriz mat)
{
  posicao = (mat * posicao.ponto4d()).vetor3d();
}

iluminacao::FonteDirecional::FonteDirecional(Vetor3d direcao,
                                             Vetor3d intensidade)
  : direcao(direcao)
  , intensidade(intensidade)
{
}

void
iluminacao::FonteDirecional::transformar(Matriz mat)
{
  direcao = (mat * direcao.vetor4d()).vetor3d();
}

iluminacao::FonteSpot::FonteSpot(Vetor3d posicao,
                                 Vetor3d direcao,
                                 float angulo,
                                 Vetor3d intensidade)
  : posicao(posicao)
  , direcao(direcao)
  , cos_beta(cos(angulo))
  , intensidade(intensidade)
{
}

void
iluminacao::FonteSpot::transformar(Matriz mat)
{
  posicao = (mat * posicao.ponto4d()).vetor3d();
  direcao = (mat * direcao.vetor4d()).vetor3d();
}

Vetor3d
iluminacao::modelo_phong(Vetor3d Pt,
                         Vetor3d dr,
                         Vetor3d n,
                         FontePontual fonte,
                         MaterialSimples material)
{
  Vetor3d v = dr * -1;
  Vetor3d l = (fonte.posicao - Pt).normalizado();
  float dotproduct_nl = n.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * n - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d E_d = material.K_d * fonte.intensidade * max(dotproduct_nl, 0.0);
  Vetor3d E_e =
    material.K_e * fonte.intensidade * pow(max(dotproduct_vr, 0.0), material.m);

  Vetor3d E_total = E_d + E_e;
  return E_total;
}

Vetor3d
iluminacao::modelo_phong(Vetor3d Pt,
                         Vetor3d dr,
                         Vetor3d n,
                         FonteDirecional fonte,
                         MaterialSimples material)
{
  Vetor3d v = dr * -1;
  Vetor3d l = fonte.direcao;
  float dotproduct_nl = n.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * n - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d E_d = material.K_d * fonte.intensidade * max(dotproduct_nl, 0.0);
  Vetor3d E_e =
    material.K_e * fonte.intensidade * pow(max(dotproduct_vr, 0.0), material.m);

  Vetor3d E_total = E_d + E_e;
  return E_total;
}

Vetor3d
iluminacao::modelo_phong(Vetor3d Pt,
                         Vetor3d dr,
                         Vetor3d n,
                         FonteSpot fonte,
                         MaterialSimples material)
{
  Vetor3d v = dr * -1;
  Vetor3d l = (fonte.posicao - Pt).normalizado();
  float cos_alpha = -l.dot_product(fonte.direcao);
  float dotproduct_nl = n.dot_product(l);
  Vetor3d r = 2 * dotproduct_nl * n - l;
  float dotproduct_vr = v.dot_product(r);

  Vetor3d I_F = fonte.intensidade;
  if (cos_alpha < fonte.cos_beta)
    I_F = max(cos_alpha, 0.0f) * I_F;

  Vetor3d E_d = material.K_d * I_F * max(dotproduct_nl, 0.0);
  Vetor3d E_e = material.K_e * I_F * pow(max(dotproduct_vr, 0.0), material.m);

  Vetor3d E_total = E_d + E_e;
  return E_total;
}

Vetor3d
iluminacao::luz_ambiente(Vetor3d I_A, Vetor3d K_a)
{
  return K_a * I_A;
}