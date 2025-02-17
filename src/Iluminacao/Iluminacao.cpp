//
// Created by Vitor de Albuquerque on 16/12/2024.
//

#include "Iluminacao.h"
#include <math.h>
using namespace iluminacao;
iluminacao::FontePontual::FontePontual(Vetor3d posicao, Vetor3d intensidade)
  : posicao(posicao)
  , intensidade(intensidade)
{
}

void FontePontual::transformar(Matriz mat) {
    // Para posição, usamos p=(x,y,z,1)
    posicao = (mat * posicao.ponto4d()).vetor3d();
}

FonteDirecional::FonteDirecional(Vetor3d dir, Vetor3d intens)
    : direcao(dir.normalizado()), intensidade(intens) {}

void FonteDirecional::transformar(Matriz mat) {
    // Para direção, usamos v=(x,y,z,0)
    direcao = (mat * direcao.vetor4d()).vetor3d().normalizado();
}

FonteSpot::FonteSpot(Vetor3d pos, Vetor3d dir, float ang, float exp, Vetor3d I)
    : posicao(pos), direcao(dir.normalizado()),
      anguloCutOff(ang), expoente(exp), intensidade(I) {}

void FonteSpot::transformar(Matriz mat) {
    posicao = (mat * posicao.ponto4d()).vetor3d();
    direcao = (mat * direcao.vetor4d()).vetor3d().normalizado();
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
Vetor3d modelo_phong_direcional(
    Vetor3d Pt,
    Vetor3d dr,
    Vetor3d n,
    FonteDirecional fonte,
    Vetor3d I_A,
    MaterialSimples material)
{
    Vetor3d v = (-1.0f) * dr;

    Vetor3d l = (-1.0f) * fonte.direcao;
    float dot_nl = n.dot_product(l);

    Vetor3d r = 2.0f * dot_nl * n - l;
    float dot_vr = v.dot_product(r);

    // Ambiente
    Vetor3d E_a = material.K_a * I_A;
    // Difusa
    Vetor3d E_d = material.K_d * fonte.intensidade * std::max(dot_nl, 0.0f);
    // Especular
    Vetor3d E_e = material.K_e * fonte.intensidade *
                  powf(std::max(dot_vr, 0.0f), material.m);

    return E_a + E_d + E_e;
}

Vetor3d modelo_phong_spot(
    Vetor3d Pt,
    Vetor3d dr,
    Vetor3d n,
    FonteSpot fonte,
    Vetor3d I_A,
    MaterialSimples material)
{
    Vetor3d v = (-1.0f) * dr;

    Vetor3d l = (fonte.posicao - Pt).normalizado();

    float cosAlfa = l.dot_product(fonte.direcao);

    float cosCutoff = cosf(fonte.anguloCutOff * (3.1415926f / 180.0f));

    if (cosAlfa < cosCutoff) {
        // Fora do cone de luz => apenas ambiente
        return material.K_a * I_A;
    }

    float spotFactor = powf(cosAlfa, fonte.expoente);
    float dot_nl = n.dot_product(l);
    Vetor3d r = 2.0f * dot_nl * n - l;
    float dot_vr = v.dot_product(r);

    Vetor3d E_a = material.K_a * I_A;
    Vetor3d E_d = material.K_d * fonte.intensidade
                  * std::max(dot_nl, 0.0f)
                  * spotFactor;
    Vetor3d E_e = material.K_e * fonte.intensidade
                  * powf(std::max(dot_vr, 0.0f), material.m)
                  * spotFactor;

    return E_a + E_d + E_e;
}

Vetor3d luz_ambiente(Vetor3d I_A, Vetor3d K_a)
{
    return K_a * I_A;
}
