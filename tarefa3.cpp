#include <math.h>
#include <raylib.h>
#include "funcoes_auxiliares.h"

// definicao das dimensoes da janela
const int W_C = 500;
const int H_C = 500;

// definicao das dimensoes do frame
const float W_J = 60.0f;
const float H_J = 60.0f;

// definicao do numero de linhas do frame
const int nLin = 500;

// definicao do numero de colunas do frame
const int nCol = 500;

// distancia do frame ao olho
float d = 30.0f;

// definicao da esfera da cena
Vetor3d K_d_esfera = {0.7, 0.2, 0.2};
Vetor3d K_e_esfera = {0.7, 0.2, 0.2};
Vetor3d K_a_esfera = {0.7, 0.2, 0.2};
float R = 40.0f;
float m_esfera = 10
Esfera esfera({0.0f, 0.0f, -100.0f}, R, K_d_esfera, K_e_esfera, K_a_esfera, m_esfera);

// definicao do plano do chao
Vetor3d K_d_plano_chao = {0.2f, 0.7f, 0.2f};
Vetor3d K_e_plano_chao = {0.0f, 0.0f, 0.0f};
Vetor3d K_a_plano_chao = {0.2f, 0.7f, 0.2f};
float m_plano_chao = 1;
Plano plano_chao({0.0f, -R, 0.0f}, {0.0f, 1.0f, 0.0f}, K_d_plano_chao, K_e_plano_chao, K_a_plano_chao, m_plano_chao);

// definicao do plano de fundo
Vetor3d K_d_plano_fundo = {0.3f, 0.3f, 0.7f};
Vetor3d K_e_plano_fundo = {0.0f, 0.0f, 0.0f};
Vetor3d K_a_plano_fundo = {0.3f, 0.3f, 0.7f};
float m_plano_fundo = 1;
Plano plano_chao({0.0f, 0.0f, -200.0f}, {0.0f, 0.0f, 1.0f}, K_d_plano_fundo, K_e_plano_fundo, K_a_plano_fundo, m_plano_fundo);

// definicao da fonte luminosa
Vetor3d I_F = {0.7f, 0.7f, 0.7f};
Vetor3d P_F = {0.0f, 60.0f, -30.0f};

// definicao da iluminacao ambiente
Vetor3d I_A = {0.3f, 0.3f, 0.3f};

int main(void)
{
    InitWindow(W_C, H_C, "Tarefa 03");
    SetTargetFps(60);

    double deltinhax = width / col, deltinhay = height / lin;
    int Deltax = SCREEN_WIDTH / col, Deltay = SCREEN_HEIGHT / lin;
    Vetor3d Ponto_Superior_Esquerdo = { -width * 0.5, height * 0.5, -dist_ao_quadro };
    float zp = -dist_ao_quadro;
    Vetor3d P0 = {0.0f, 0.0f, 0.0f};

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            for (int i = 0; i < lin; ++i) {
                float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5 - i*deltinhay;
                for (int j = 0; j < col; ++j) {
                    float xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5 * deltinhax;
                    Vetor3d P = { xp, yp, zp };
                    Vetor3d dr = funcoes_auxiliares::Vetor3dNormalizado(P);
                    Raio raio(P0, dr);
                    float t_esfera = raio.intersecao(esfera);
                    float t_plano_chao = raio.intersecao(plano_chao);
                    float t_plano_fundo = raio.intersecao(plano_fundo);
                    if(t_esfera > 0.0f && t_esfera < t_plano_chao && t_esfera < t_plano_fundo) {

                    } else if(t_plano_chao > 0.0f && t_plano_chao < t_esfera && t_plano_chao < t_plano_fundo) {

                    } else if(t_plano_fundo > 0.0f && t_plano_fundo < t_esfera && t_plano_fundo < t_plano_chao) {

                    }
                }
            }

        }
        EndDrawing();
    }

    return 0;
}
