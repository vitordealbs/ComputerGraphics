#include <cstdio>
#include <math.h>
#include <raylib.h>
#include <vector>

#include "./src/Camera/Camera3de.h"
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
#include "src/ObjetoComplexo/ObjetoComplexo.h"
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
const int W_C = 600;
const int H_C = 600;
const float W_J = 60.0f;
const float H_J = 60.0f;
const int nLin = 500, nCol = 500;
const float d = 30.0f;

// Iluminação e fontes de luz
const Vetor3d I_A = { 0.2f, 0.2f, 0.2f };
const Vetor3d P_F = { 300.0f, 400.0f, 100.0f };
const Vetor3d I_F = { 1.0f, 1.0f, 1.0f };


std::vector<ObjetoComplexo> objetos_complexos;
std::vector<Objeto> objetos_flat;

// Função para "achatar" objetos complexos
void flatten_objetos(const ObjetoComplexo& objeto_complexo, std::vector<Objeto>& objetos_flat) {
  for (const auto& obj : objeto_complexo.objetos) {
    objetos_flat.push_back(obj); // Adiciona objetos simples
  }
  for (const auto& sub_objeto : objeto_complexo.objetosComplexos) {
    flatten_objetos(sub_objeto, objetos_flat); // Processa objetos complexos recursivamente
  }
}
void
inicializar_objetos()
{
  // Mesa
    Malha tampo;
    Vetor3d K_tampo = {0.0f, 0.0f, 1.0f};
    float m_tampo = 1.0f;
    tampo.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);
    tampo.transformar(Matriz::translacao({300.0f, 10.0f, 300.0f}) * // Centralize no eixo X e Z
                      Matriz::escala({250.0f, 5.0f, 150.0f}));

    Vetor3d K_suporte = {1.0f, 1.0f, 0.0f};
    Malha suporte1, suporte2;
    suporte1.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    suporte2.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    suporte1.transformar(Matriz::translacao({275.0f, 5.0f, 325.0f}) * Matriz::escala({10.0f, 90.0f, 10.0f}));
    suporte2.transformar(Matriz::translacao({325.0f, 5.0f, 275.0f}) * Matriz::escala({10.0f, 90.0f, 10.0f}));

    ObjetoComplexo mesa;
    mesa.adicionar_objeto(tampo);
    mesa.adicionar_objeto(suporte1);
    mesa.adicionar_objeto(suporte2);
    objetos_complexos.push_back(mesa);

    // Árvore de Natal
    Vetor3d dir_cima = {0.0f, 1.0f, 0.0f};
    Cilindro tronco({300.0f, 100.0f, 300.0f}, 10.0f, 50.0f, dir_cima, K_suporte, K_suporte, K_suporte, m_tampo);
    Cone folhas({300.0f, 150.0f, 300.0f}, 60.0f, 100.0f, dir_cima, K_tampo, K_tampo, K_tampo, m_tampo);
    Esfera estrela({300.0f, 250.0f, 300.0f}, 10.0f, K_tampo, K_tampo, K_tampo, m_tampo);

    ObjetoComplexo arvore;
    arvore.adicionar_objeto(tronco);
    arvore.adicionar_objeto(folhas);
    arvore.adicionar_objeto(estrela);
    objetos_complexos.push_back(arvore);

    // Galpão
    Malha coluna1, coluna2, viga, parede;
    coluna1.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    coluna2.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    viga.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    parede.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);

    coluna1.transformar(Matriz::translacao({250.0f, 50.0f, 250.0f}) * Matriz::escala({10.0f, 100.0f, 10.0f}));
    coluna2.transformar(Matriz::translacao({350.0f, 50.0f, 350.0f}) * Matriz::escala({10.0f, 100.0f, 10.0f}));
    viga.transformar(Matriz::translacao({300.0f, 100.0f, 300.0f}) * Matriz::escala({100.0f, 10.0f, 10.0f}));
    parede.transformar(Matriz::translacao({300.0f, 50.0f, 300.0f}) * Matriz::escala({200.0f, 100.0f, 10.0f}));

    ObjetoComplexo portico;
    portico.adicionar_objeto(coluna1);
    portico.adicionar_objeto(coluna2);
    portico.adicionar_objeto(viga);
    objetos_complexos.push_back(portico);


  // Paredes&Telhados
  Vetor3d K_parede = { 0.5f, 0.5f, 0.5f };
  float m_parede = 1.0f;

  // --- TELHADO ESQUERDO ---
  Malha telhado_esq;
  telhado_esq.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_parede, K_parede, K_parede, m_parede);
  telhado_esq.transformar(
    Matriz::translacao({ 300.0f, 550.0f, 150.0f }) *
    Matriz::cisalhamento_xy_y(-atan(0.75)) *
    Matriz::escala({ 600.0f, 20.0f, 300.0f }));

  // --- TELHADO DIREITO ---
  Malha telhado_dir;
  telhado_dir.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_parede, K_parede, K_parede, m_parede);
  telhado_dir.transformar(
    Matriz::translacao({ 300.0f, 550.0f, 450.0f }) *
    Matriz::cisalhamento_xy_y(atan(0.75)) *
    Matriz::escala({ 600.0f, 20.0f, 300.0f }));
  // --- PAREDE DE FECHAMENTO ESQUERDA ---
  Malha parede_esq;
  parede_esq.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_parede, K_parede, K_parede, m_parede);
  parede_esq.transformar(
    Matriz::translacao({ 0.0f, 250.0f, 300.0f }) *
    Matriz::escala({ 20.0f, 500.0f, 600.0f }));

  // --- PAREDE DE FECHAMENTO DIREITA ---
  Malha parede_dir;
  parede_dir.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_parede, K_parede, K_parede, m_parede);
  parede_dir.transformar(
    Matriz::translacao({ 600.0f, 250.0f, 300.0f }) *
    Matriz::escala({ 20.0f, 500.0f, 600.0f }));

  // --- PAREDE DE FECHAMENTO DE FUNDO ---
  Malha parede_fundo;
  parede_fundo.inicializar_cubo(
    { 0.0f, 0.0f, 0.0f }, 1.0f, K_parede, K_parede, K_parede, m_parede);
  parede_fundo.transformar(
    Matriz::translacao({ 300.0f, 250.0f, 600.0f }) *
    Matriz::escala({ 600.0f, 500.0f, 20.0f }));

  ObjetoComplexo paredeseTelhado;

  paredeseTelhado.adicionar_objeto(parede_fundo);
  paredeseTelhado.adicionar_objeto(parede_dir);
  paredeseTelhado.adicionar_objeto(parede_esq);
  paredeseTelhado.adicionar_objeto(telhado_dir);
  paredeseTelhado.adicionar_objeto(telhado_esq);

  // galpão
  ObjetoComplexo galpao;

  galpao.adicionar_objeto_complexo(paredeseTelhado);

  objetos_complexos.push_back(galpao);
}





int main(void) {
    // Inicialização da janela Raylib
    InitWindow(W_C, H_C, "Tarefa06 - Ray Tracing");
    SetTargetFPS(60);

    // Inicializar câmera
    Vetor3d Eye = {300.0f, 250.0f, 800.0f}; // Ajustar posição da câmera se necessário
    Vetor3d At = {300.0f, 250.0f, 300.0f};  // Apontando para o centro dos objetos
    Vetor3d Up = {0.0f, 1.0f, 0.0f};
    Camera3de camera(Eye, At, Up);
    Matriz M_wc = camera.getTransformationMatrix();

    inicializar_objetos();

    // Flatten todos os objetos complexos
    for (const auto& objeto_complexo : objetos_complexos) {
        flatten_objetos(objeto_complexo, objetos_flat);
    }
    for (auto& objeto : objetos_flat) {
        objeto.transformar(M_wc);
    }


    // Loop principal de renderização
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Renderizar usando Raycasting
        for (int i = 0; i < nLin; ++i) {
            for (int j = 0; j < nCol; ++j) {
                // Cálculo da posição do pixel no plano de projeção
                float x = -W_J * 0.5f + float(j) * (W_J / nCol);
                float y = H_J * 0.5f - float(i) * (H_J / nLin);
                Vetor3d P = {x, y, -30.0f};
                Vetor3d dr = P.normalizado();
                Raio raio(camera.position, dr);

                // Calcular interseção
                auto [t, idx] = calcular_intersecao(raio, objetos_flat);
                if (t > 0.0f) {
                    Vetor3d Pt = raio.no_ponto(t); // Ponto de interseção
                    Vetor3d normal = objetos_flat[idx].normal(Pt); // Normal no ponto de interseção



                    // Iluminação Phong
                    Vetor3d dr_luz = (P_F - Pt).normalizado();
                    Raio raio_luz(Pt, dr_luz);
                    auto [t_luz, _] = calcular_intersecao(raio_luz, objetos_flat, idx);

                    MaterialSimples material = objetos_flat[idx].material;
                    Vetor3d I_total = I_A;
                    if (t_luz < 0.0f || t_luz > (P_F - Pt).tamanho()) {
                        I_total = iluminacao::modelo_phong(Pt, raio.dr, normal, { P_F, I_F }, I_A, material);
                    } else {
                        I_total = iluminacao::luz_ambiente(I_A, material.K_a);
                    }



                    // Definir cor do pixel
                    Color pixel_color = {
                        static_cast<unsigned char>(fmin(I_total.x * 255, 255)),
                        static_cast<unsigned char>(fmin(I_total.y * 255, 255)),
                        static_cast<unsigned char>(fmin(I_total.z * 255, 255)),
                        255
                    };

                    DrawPixel(j, i, pixel_color);
                } else {
                    DrawPixel(j, i, RED);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
