#include <math.h>
#include <raylib.h>
#include <cstdio>
#include "funcoes_auxiliares.h"
#include "funcoes_auxiliares_de_modelacao.h"
using namespace funcoes_auxiliares;
using namespace Auxiliares_de_modelacao;


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
float m_esfera = 10;
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
Plano plano_fundo({0.0f, 0.0f, -200.0f}, {0.0f, 0.0f, 1.0f}, K_d_plano_fundo, K_e_plano_fundo, K_a_plano_fundo, m_plano_fundo);

// definicao da fonte luminosa
Vetor3d I_F = {0.7f, 0.7f, 0.7f};
Vetor3d P_F = {0.0f, 60.0f, -30.0f};

// definicao da iluminacao ambiente
Vetor3d I_A = {0.3f, 0.3f, 0.3f};

int main(void)
{
    InitWindow(W_C, H_C, "Tarefa 03");
    SetTargetFPS(60);

    double deltinhax = W_J / nCol, deltinhay = H_J / nLin;
    int Deltax = W_C / nCol, Deltay = H_C / nLin;
    Vetor3d Ponto_Superior_Esquerdo = { -W_J * 0.5f, W_J * 0.5f, -d };
    float zp = -d;
    Vetor3d P0 = {0.0f, 0.0f, 0.0f};

    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            for (int i = 0; i < nLin; ++i) {
                float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5 - i*deltinhay;
                for (int j = 0; j < nCol; ++j) {
                    float xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5 * deltinhax;
                    Vetor3d P = { xp, yp, zp };
                    Vetor3d dr = Auxiliares::Vetor3dNormalizado(P);
                    Raio raio(P0, dr);
                    float t_esfera = raio.intersecao(esfera);
                    float t_plano_chao = raio.intersecao(plano_chao);
                    float t_plano_fundo = raio.intersecao(plano_fundo);
                    Vetor3d I_total = I_A;
                    if(t_esfera > 0.0f && (t_esfera < t_plano_chao || t_plano_chao < 0.0f) && (t_esfera < t_plano_fundo || t_plano_fundo < 0.0f)) {
                        Vetor3d Pt = raio.no_ponto(t_esfera);
                        I_total = esfera.calcular_iluminacao(Pt, raio.dr, P_F, I_F, I_A);
                    } else if(t_plano_chao > 0.0f && (t_plano_chao < t_esfera || t_esfera < 0.0f) && (t_plano_chao < t_plano_fundo || t_plano_fundo < 0.0f)) {
                        Vetor3d Pt = raio.no_ponto(t_plano_chao);
                        Vetor3d dr_luz = Auxiliares::Vetor3d_Subtrai(P_F, Pt);
                        Raio raio_luz(Pt, dr_luz);
                        if(raio_luz.intersecao(esfera) < 0.0) {
                            I_total = plano_chao.calcular_iluminacao(Pt, raio.dr, P_F, I_F, I_A);
                        } else {
                            I_total = plano_chao.calcular_iluminacao(Pt, raio.dr, P_F, {0.0f, 0.0f, 0.0f}, I_A);
                        }

                    } else if(t_plano_fundo > 0.0f && (t_plano_fundo < t_esfera || t_esfera < 0.0f) && (t_plano_fundo < t_plano_chao || t_plano_chao < 0.0f)) {
                        Vetor3d Pt = raio.no_ponto(t_plano_fundo);
                        Vetor3d dr_luz = Auxiliares::Vetor3d_Subtrai(P_F, Pt);
                        Raio raio_luz(Pt, dr_luz);
                        if(raio_luz.intersecao(esfera) < 0.0) {
                            I_total = plano_fundo.calcular_iluminacao(Pt, raio.dr, P_F, I_F, I_A);
                        } else {
                            I_total = plano_chao.calcular_iluminacao(Pt, raio.dr, P_F, {0.0f, 0.0f, 0.0f}, I_A);
                        }
                    }

                    DrawRectangle(
              Deltax * j,
              Deltay * i,
              Deltax,
              Deltay,
              (Color){ static_cast<unsigned char>(min(I_total.x * 255.0f, 255.0f)),
    				   static_cast<unsigned char>(min(I_total.y * 255.0f, 255.0f)),
    				   static_cast<unsigned char>(min(I_total.z * 255.0f, 255.0f)),
    																	  255});
                }
            }

        }
        EndDrawing();
    }

    return 0;
}
