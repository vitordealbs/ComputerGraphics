#include "PlanoTextura.h"

PlanoTextura::PlanoTextura(Vetor3d ponto,
                           Vetor3d eixo1,
                           Vetor3d eixo2,
                           Textura textura)
  : ponto(ponto)
  , eixo1(eixo1)
  , eixo2(eixo2)
  , textura(textura)
{
  normal = eixo1.cross_product(eixo2).normalizado();
}

MaterialSimples
PlanoTextura::material(Vetor3d Pt)
{
  Vetor3d v = Pt - ponto;
  float x = v.dot_product(eixo1);
  float y = v.dot_product(eixo2);

  Color pixel = textura.at(x, y);
  Vetor3d K = { pixel.r / 255.0f, pixel.g / 255.0f, pixel.b / 255.0f };
  MaterialSimples material(K, K, K, textura.m);
  return material;
}
