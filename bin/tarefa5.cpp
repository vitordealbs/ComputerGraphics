#include <math.h>
#include <cstdio>
#include <raylib.h>
#include <vector>

#include "funcoes_auxiliares.h"
#include "./src/Circulo/Circulo.h"
#include "./src/Cilindro/Cilindro.h"
#include "./src/Cone/Cone.h"
#include "./src/Esfera/Esfera.h"
#include "./src/Iluminacao/Iluminacao.h"
#include "./src/Material/Material.h"
#include "./src/Plano/Plano.h"
#include "./src/Raio/Raio.h"
#include "./src/Triangulo/Triangulo.h"
#include "./src/Objeto/Objeto.h"
#include "./src/Malha/Malha.h"

using namespace funcoes_auxiliares;

// Função para calcular interseção
std::pair<float, int>
calcular_intersecao(Raio raio, const std::vector<Objeto>& objetos, int excluir = -1)
{
    int objeto = -1;
    float menor_t = -1.0f;
    float t;

    for (int i = 0; i < objetos.size(); ++i) {
        if (i == excluir) continue;
        if ((t = raio.intersecao(objetos[i])) > 0.0f && (menor_t < 0.0f || t < menor_t)) {
            menor_t = t;
            objeto = i;
        }
    }

    return {menor_t, objeto};
}

// Dimensões da janela e frame
const int W_C = 500;
const int H_C = 500;
const float W_J = 60.0f;
const float H_J = 60.0f;
const int nLin = 500, nCol = 500;
float d = 30.0f;

// Declaração de objetos da cena
float R = 5.0f;

// Esfera

Vetor3d K_d_esfera = {0.854, 0.647, 0.125};
Vetor3d K_e_esfera = K_d_esfera;
Vetor3d K_a_esfera = K_d_esfera;
Esfera esfera({0.0f, 95.0f, -200.0f}, R, K_d_esfera, K_e_esfera, K_a_esfera, 10.0f);

// Plano do chão
Vetor3d K_d_plano_chao = {0.2f, 0.7f, 0.2f};
Vetor3d K_e_plano_chao = {0.0f, 0.0f, 0.0f};
Vetor3d K_a_plano_chao = {0.2f, 0.7f, 0.2f};
Plano plano_chao({0.0f, -150.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, K_d_plano_chao, K_e_plano_chao, K_a_plano_chao, 1.0f);

// Plano de fundo
Vetor3d K_d_plano_fundo = {0.3f, 0.3f, 0.7f};
Plano plano_fundo({0.0f, 0.0f, -200.0f}, {0.0f, 0.0f, 1.0f}, K_d_plano_fundo, K_d_plano_fundo, K_d_plano_fundo, 1.0f);

// Parede Lateral Direita
Vetor3d K_d_parede_lateral_direita = {0.686f, 0.933f, 0.933f};
Plano plano_parede_lateral_direita({200.0f, -50.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, K_d_parede_lateral_direita, K_d_parede_lateral_direita, K_d_parede_lateral_direita, 1.0f);

// Parede Lateral Esquerda

Vetor3d K_d_parede_lateral_esquerda = {0.686f, 0.933f, 0.933f};
Plano plano_parede_lateral_esquerda({-200.0f, -150.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, K_d_parede_lateral_esquerda, K_d_parede_lateral_esquerda, K_d_parede_lateral_esquerda, 1.0f);

// Plano Teto
Vetor3d K_d_teto = {0.933f, 0.933f, 0.933f};
Plano plano_teto({200.0f, 150.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, K_d_teto, K_d_teto, K_d_teto, 1.0f);

// Cilindro
Vetor3d K_d_cilindro = {0.824f, 0.706, 0.549};
Cilindro cilindro({0.0f, -150.0f, -200.0f}, R , 90.0f, {0.0f, 1.0f, 0.0f}, K_d_cilindro, K_d_cilindro, K_d_cilindro, 1.0f);

// Cone
Vetor3d K_d_cone = {0, 1, 0.498};
Cone cone({0.0f, -60.0f, -200.0f}, 90.0f, 150.0f, {0.0f, 1.0f, 0.0f}, K_d_cone, K_d_cone, K_d_cone, 1.0f);

// Cubo
Vetor3d centro_cubo = {50.0f, -130.0f, -200.0f};
float tamanho_cubo = 40.0f;
Vetor3d K_d_cubo = {1.0f, 0.078f, 0.576f};
float m_cubo = 10.0f;

// Vetor de objetos
std::vector<Objeto> objetos;

void inicializar_objetos() {
    objetos.push_back(Objeto(esfera));
    objetos.push_back(Objeto(plano_chao));
    objetos.push_back(Objeto(plano_fundo));
    objetos.push_back(Objeto(plano_teto));
    objetos.push_back(Objeto(plano_parede_lateral_esquerda));
    objetos.push_back(Objeto(plano_parede_lateral_direita));
    objetos.push_back(Objeto(cone));
    objetos.push_back(Objeto(cilindro));
    Malha malha_cubo;
    malha_cubo.inicializar_cubo({50.0f, -130.0f, -200.0f}, 40.0f, {0.0f, 1.0f, 0.0f}, K_d_cubo, K_d_cubo, K_d_cubo, m_cubo);

    for (const auto& triangulo : malha_cubo.faces) {
        objetos.push_back(Objeto(triangulo));
    }
}

// definicao da fonte luminosa
Vetor3d I_F = { 0.7f, 0.7f, 0.7f };
Vetor3d P_F = { -100.0f, 140.0f, -20.0f };

// definicao da iluminacao ambiente
Vetor3d I_A = { 0.3f, 0.3f, 0.3f };



int main() {
    // Inicialização
    InitWindow(W_C, H_C, "Cena Raylib");
    Texture2D textura_madeira = LoadTexture("../assets/madeira.png");
    inicializar_objetos();
    SetTargetFPS(60);

    double deltinhax = W_J / nCol, deltinhay = H_J / nLin;
    Vetor3d Ponto_Superior_Esquerdo = {-W_J * 0.5f, W_J * 0.5f, -d};
    Vetor3d P0 = {0.0f, 0.0f, 150.0f};

    // Loop principal
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Desenhar textura do chão
        DrawTexture(textura_madeira, 0, H_C / 2, WHITE);


        for (int i = 0; i < nLin; ++i) {
            float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5f - i * deltinhay;
            for (int j = 0; j < nCol; ++j) {
                float xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5f * deltinhax;
                Vetor3d P = {xp, yp, -d};
                Vetor3d dr = P.normalizado();
                Raio raio(P0, dr);

                auto [t, objeto] = calcular_intersecao(raio, objetos);
                Vetor3d I_total = I_A;

                if (t > 0.0f) {
                    Vetor3d Pt = raio.no_ponto(t);
                    I_total = iluminacao::modelo_phong(Pt, raio.dr, objetos[objeto].normal(Pt), {P_F, I_F}, I_A, objetos[objeto].material);
                }

                Color pixel = {
                    static_cast<unsigned char>(fmin(I_total.x * 255, 255)),
                    static_cast<unsigned char>(fmin(I_total.y * 255, 255)),
                    static_cast<unsigned char>(fmin(I_total.z * 255, 255)),
                    255};

                DrawPixel(j, i, pixel);
            }
        }
        EndDrawing();
    }

    UnloadTexture(textura_madeira);
    CloseWindow();
    return 0;
}
