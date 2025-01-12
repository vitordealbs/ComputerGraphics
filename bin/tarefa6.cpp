#include <cstdio>
#include <iostream>
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
const Vetor3d P_F = { -300.0f, 128.0f, 100.0f };
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
Image textura_madeira;
Color* pixels_textura_madeira;
void
inicializar_objetos()
{

    //textura do piso
    Image textura_madeira = LoadImage("../assets/madeira.png");
    Color* pixels_textura_madeira = LoadImageColors(textura_madeira);
    Textura textura(pixels_textura_madeira,
                    textura_madeira.width,
                    textura_madeira.height,
                    textura_madeira.width / 10.0f,
                    textura_madeira.height / 10.0f,
                    1.0f);
    PlanoTextura plano_chao({ 0.0f, -150.0f, 0.0f },
                            { 1.0f, 0.0f, 0.0f },
                            { 0.0f, 0.0f, -1.0f },
                            textura);
    std::cout << "Inicializou plano chao.\n";
    if (textura_madeira.data == nullptr) {
        std::cerr << "Erro ao carregar textura madeira.\n";
        return;
    }
    objetos_flat.push_back(plano_chao);

    //textura do piso
    Image textura_ceu = LoadImage("../assets/ceu.png");
    Color* pixels_textura_ceu = LoadImageColors(textura_ceu);
    Textura textura2(pixels_textura_ceu,
                    textura_madeira.width,
                    textura_madeira.height,
                    textura_madeira.width / 10.0f,
                    textura_madeira.height / 10.0f,
                    1.0f);
    PlanoTextura plano_ceu({ 300.0f, 250.0f, 10000.0f },
                            { 1.0f, 0.0f, 0.0f },
                            { 0.0f, 1.0f, 0.0f },
                            textura2);
    std::cout << "Inicializou plano chao.\n";
    if (textura_madeira.data == nullptr) {
        std::cerr << "Erro ao carregar textura madeira.\n";
        return;
    }
    objetos_flat.push_back(plano_ceu);

  objetos_flat.emplace_back(plano_chao);
  // Mesa
    Malha tampo;
    Vetor3d K_tampo = {0.6f, 0.3f, 0.1f};
    float m_tampo = 1.0f;
    tampo.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);
    tampo.transformar(Matriz::translacao({300.0f, 50.0f, 300.0f}) * // Centralize no eixo X e Z
                      Matriz::escala({250.0f, 5.0f, 150.0f}));

    Vetor3d K_suporte = {1.0f, 0.5f, 0.5f};
    Vetor3d K_estrela = {1.0f, 1.0f, 0.0f};
    Vetor3d K_tronco = {0.65f, 0.33f, 0.16f};
    Vetor3d K_folhas = {0.0f, 0.39f, 0.0f};
    Malha suporte1, suporte2;
    suporte1.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    suporte2.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    suporte1.transformar(Matriz::translacao({175.0f, 2.0f, 300.0f}) * Matriz::escala({5.0f, 95.0f, 150.0f}));
    suporte2.transformar(Matriz::translacao({425.0f, 2.0f, 300.0f}) * Matriz::escala({5.0f, 95.0f, 150.0f}));

    ObjetoComplexo mesa;
    mesa.adicionar_objeto(tampo);
    mesa.adicionar_objeto(suporte1);
    mesa.adicionar_objeto(suporte2);
    objetos_complexos.push_back(mesa);

    // Árvore de Natal
    Vetor3d dir_cima = {0.0f, 1.0f, 0.0f};
    Cilindro tronco({300.0f, 55.0f, 300.0f}, 6.0f, 40.0f, dir_cima, K_tronco, K_tronco, K_tronco, 10.0f);
    Cone folhas({300.0f, 100.0f, 300.0f}, 60.0f, 150.0f, dir_cima, K_folhas, K_folhas, K_folhas, m_tampo);
    Esfera estrela({300.0f, 250.0f, 300.0f}, 4.5f, K_estrela, K_estrela, K_estrela, m_tampo);
    Cilindro suporte_arvore({300.0f, 55.0f, 300.0f}, 30.0f, 9.0f, dir_cima, K_estrela, K_estrela, K_estrela, 10.0f);
    Circulo suporte_arvore_circulo({300.0f, 64.0f, 300.0f}, 30.0f,{0.0f,1.0f,0.0f} , K_estrela, K_estrela, K_estrela, 10.0f);

    ObjetoComplexo arvore;
    arvore.adicionar_objeto(tronco);
    arvore.adicionar_objeto(folhas);
    arvore.adicionar_objeto(estrela);
    arvore.adicionar_objeto(suporte_arvore);
    arvore.adicionar_objeto(suporte_arvore_circulo);
    objetos_complexos.push_back(arvore);

    // Galpão
    Malha coluna1, coluna2, viga1, viga2, parede;
    coluna1.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);
    coluna2.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    viga1.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    viga2.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_suporte, K_suporte, K_suporte, m_tampo);
    parede.inicializar_cubo({0.0f, 0.0f, 0.0f}, 1.0f, K_tampo, K_tampo, K_tampo, m_tampo);

    coluna1.transformar(Matriz::translacao({250.0f, 50.0f, 250.0f}) * Matriz::escala({50.0f, 500.0f, 30.0f}));
    coluna2.transformar(Matriz::translacao({350.0f, 50.0f, 350.0f}) * Matriz::escala({50.0f, 500.0f, 30.0f}));
    viga1.transformar( Matriz::escala({300.0f, 50.0f, 30.0f})* Matriz::cisalhamento_xy_x(75) * Matriz::translacao({300.0f, 100.0f, 300.0f}) );
    viga2.transformar( Matriz::escala({300.0f, 50.0f, 30.0f})* Matriz::translacao({300.0f, 100.0f, 300.0f}) );
    parede.transformar(Matriz::translacao({300.0f, 50.0f, 300.0f}) * Matriz::escala({200.0f, 100.0f, 10.0f}));

    ObjetoComplexo portico;
    portico.adicionar_objeto(coluna1);
    portico.adicionar_objeto(coluna2);
    portico.adicionar_objeto(viga1);
    portico.adicionar_objeto(viga2);
    objetos_complexos.push_back(portico);

/*
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
  */
}

void
deletar_objetos()
{
    UnloadImageColors(pixels_textura_madeira);
    UnloadImage(textura_madeira);
}



int main(void) {
    InitWindow(W_C, H_C, "Tarefa06 - Ray Tracing");
    SetTargetFPS(60);

    // Inicializar câmera
    Vetor3d Eye = {300.0f, 150.0f, -500.0f};
    Vetor3d At = {300.0f, 150.0f, 300.0f};
    Vetor3d Up = {0.0f, 1.0f, 0.0f};
    Camera3de camera(Eye, At, Up);
    Matriz M_wc = camera.getTransformationMatrix();

    inicializar_objetos();

    for (const auto& objeto_complexo : objetos_complexos) {
        flatten_objetos(objeto_complexo, objetos_flat);
    }
    for (auto& objeto : objetos_flat) {
        objeto.transformar(M_wc);
    }
    std::cout << "Objetos na cena: " << objetos_flat.size() << "\n";
    // Loop principal
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < nLin; ++i) {
            for (int j = 0; j < nCol; ++j) {
                float x = -W_J * 0.5f + float(j) * (W_J / nCol);
                float y = H_J * 0.5f - float(i) * (H_J / nLin);
                Vetor3d P = {x, y, -d};
                Vetor3d dr = P.normalizado();
                Raio raio(camera.position, dr);

                auto [t, objeto] = calcular_intersecao(raio, objetos_flat);
                Vetor3d I_total = I_A;
                MaterialSimples material;

                if (t > 0.0f) {
                    Vetor3d Pt = raio.no_ponto(t);
                    Vetor3d normal = objetos_flat[objeto].normal(Pt);

                    std::visit([&](auto&& obj) {
                        using T = std::decay_t<decltype(obj)>;
                        if constexpr (std::is_same_v<T, PlanoTextura>) {
                            material = obj.material(Pt);
                        } else {
                            material = objetos_flat[objeto].material;
                        }
                    }, objetos_flat[objeto].obj);

                    Vetor3d dr_luz = (P_F - Pt).normalizado();
                    Raio raio_luz(Pt, dr_luz);
                    auto [t_luz, _] = calcular_intersecao(raio_luz, objetos_flat, objeto);

                    if (t_luz < 0.0f || t_luz > (P_F - Pt).tamanho()) {
                        I_total = iluminacao::modelo_phong(Pt, raio.dr, normal, {P_F, I_F}, I_A, material);
                    } else {
                        I_total = iluminacao::luz_ambiente(I_A, material.K_a);
                    }

                    Color pixel_color = {
                        static_cast<unsigned char>(fmin(I_total.x * 255, 255)),
                        static_cast<unsigned char>(fmin(I_total.y * 255, 255)),
                        static_cast<unsigned char>(fmin(I_total.z * 255, 255)),
                        255
                    };

                    DrawPixel(j, i, pixel_color);
                } else {
                    DrawPixel(j, i, WHITE);
                }
            }
        }

        EndDrawing();
    }

    deletar_objetos();
    CloseWindow();

    return 0;
}
