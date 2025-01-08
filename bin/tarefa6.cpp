#include <cstdio>
#include <math.h>
#include <raylib.h>
#include <vector>

#include "./src/Camera/Camera.h"
#include "./src/Cilindro/Cilindro.h"
#include "./src/Circulo/Circulo.h"
#include "./src/Cone/Cone.h"
#include "./src/Esfera/Esfera.h"
#include "./src/Iluminacao/Iluminacao.h"
#include "./src/Malha/Malha.h"
#include "./src/Material/Material.h"
#include "./src/Objeto/Objeto.h"
#include "./src/Plano/Plano.h"
#include "./src/Raio/Raio.h"
#include "./src/Triangulo/Triangulo.h"
#include "funcoes_auxiliares.h"

using namespace funcoes_auxiliares;

// Função para calcular interseção
std::pair<float, int>
calcular_intersecao(Raio raio,
                    const std::vector<Objeto>& objetos,
                    int excluir = -1)
{
  int objeto = -1;
  float menor_t = -1.0f;
  float t;

  for (int i = 0; i < objetos.size(); ++i) {
    if (i == excluir)
      continue;
    if ((t = raio.intersecao(objetos[i])) > 0.0f &&
        (menor_t < 0.0f || t < menor_t)) {
      menor_t = t;
      objeto = i;
    }
  }

  return { menor_t, objeto };
}

// Dimensões da janela e frame
const int W_C = 500;
const int H_C = 500;
const float W_J = 60.0f;
const float H_J = 60.0f;
const int nLin = 500, nCol = 500;

void
inicializar_objetos()
{
  // mesa
  Malha tampo;
  Vetor3d K_tampo = { 0.0f, 0.0f, 1.0f };
  float m_tampo = 1.0f;
  tampo.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);
  tampo.transformar(Matriz::translacao({125.0f, 95.0f + 2.5f, 75.0f}) * Matriz::escala({250.0f, 5.0f, 150.0f}));
  Vetor3d K_suporte = { 1.0f, 1.0f, 0.0f };
  float m_suporte = 1.0f;
  Malha suporte1;
  suporte1.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_suporte, K_suporte, K_suporte, m_suporte);
  suporte1.transformar(Matriz::translacao({2.5f, 95.0f * 0.5f, 75.0f}) * Matriz::escala({5.0f, 95.0f, 150.0f}));
  Malha suporte2;
  suporte2.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_suporte, K_suporte, K_suporte, m_suporte);
  suporte2.transformar(Matriz::translacao({250.0f - 2.5f, 95.0f * 0.5f, 75.0f}) * Matriz::escala({5.0f, 95.0f, 150.0f}));
  ObjetoComplexo mesa;
  mesa.adicionar_objeto(tampo);
  mesa.adicionar_objeto(suporte1);
  mesa.adicionar_objeto(suporte2);
  // arvore
  Vetor3d dir_cima = {0.0f, 1.0f, 0.0f};
  Vetor3d K_madeira = {0.8f, 0.8f, 0.3f};
  float m_madeira = 1.0f;
  Vetor3d K_folha = {0.0f, 0.8f, 0.0f};
  float m_folha = 1.0f;
  Vetor3d K_bola = {1.0f, 1.0f, 0.2f};
  float m_bola = 100.0f;
  Cilindro suporte_arvore({0.0f, 0.0f, 0.0f}, 30.0f, 9.0f, dir_cima, K_madeira, K_madeira, K_madeira, m_madeira);
  Cilindro tronco_arvore({0.0f, 9.0f, 0.0f}, 6.0f, 40.0f, dir_cima, K_madeira, K_madeira, K_madeira, m_madeira);
  Cone cone_arvore({0.0f, 49.0f, 0.0f}, 60.0f, 150.0f, dir_cima, K_folha, K_folha, K_folha, m_folha);
  Esfera bola_arvore({0.0f, 199.0f + 4.5f * 0.5f, 0.0f}, 4.5f, K_bola, K_bola, K_bola, m_bola);
  ObjetoComplexo arvore;
  arvore.adicionar_objeto(suporte_arvore);
  arvore.adicionar_objeto(tronco_arvore);
  arvore.adicionar_objeto(cone_arvore);
  arvore.adicionar_objeto(bola_arvore);
  // pórtico
  Malha coluna_esq;
  coluna_esq.inicializar_cubo(
    {0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_suporte);
  coluna_esq.transformar(Matriz::translacao({-25.0f, 250.0f, 15.0f}) * Matriz::escala({50.0f, 500.0f, 30.0f}));
  Malha coluna_dir;
  coluna_dir.inicializar_cubo(
    {0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_suporte);
  coluna_dir.transformar(Matriz::translacao({600.0f, 250.0f, 15.0f}) * Matriz::escala({50.0f, 500.0f, 30.0f}));
  Malha viga_esq;
  viga_esq.inicializar_cubo(
    {0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_suporte);
  viga_esq.transformar(Matriz::translacao({600.0f, 250.0f, 15.0f}) * Matriz::cisalhamento_xy_y(atan(0.75)) * Matriz::escala({300.0f, 50.0f, 30.0f}));
}