#include <math.h>
#include <raylib.h>
#include <cstdio>
#include "funcoes_auxiliares.h"

double
max(double a, double b)
{
    return a + (b - a) * (a < b);
}

double min(double a, double b)
{
    return a + (b - a) * (a > b);
}

struct Plano {
    Vetor3d ponto;
    Vetor3d normal;

    Vetor3d K_d;
    Vetor3d K_e;
    Vetor3d K_a;
    float m;

    Plano(Vetor3d ponto, Vetor3d normal, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m) : ponto(ponto), normal(normal), K_d(K_d), K_e(K_e), K_a(K_a), m(m) {}

    Vetor3d calcular_iluminacao(Vetor3d Pt, Vetor3d dr, Vetor3d P_F, Vetor3d I_F, Vetor3d I_A) {
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(dr, -1);
        Vetor3d l = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt));
        Vetor3d n = normal;
        float dotproduct_nl = funcoes_auxiliares::Vetor3DotProduct(n, l);
        Vetor3d r = funcoes_auxiliares::Vetor3d_Subtrai(funcoes_auxiliares::Vetor3d_escala(n, 2 * dotproduct_nl), l);
        float dotproduct_vr = funcoes_auxiliares::Vetor3DotProduct(v, r);

        Vetor3d I_d = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K_d, I_F), dotproduct_nl);
        Vetor3d I_e = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K_e, I_F), pow(dotproduct_vr, m));
        Vetor3d I_a = funcoes_auxiliares::Vetor3d_Multiplica(K_a, I_A);

        Vetor3d I_total = funcoes_auxiliares::Vetor3d_Adiciona(I_d, funcoes_auxiliares::Vetor3d_Adiciona(I_e, I_a));
        return I_total;
    }
};

struct Esfera {
    Vetor3d centro;
    float raio;

    Vetor3d K_d;
    Vetor3d K_e;
    Vetor3d K_a;
    float m;

    Esfera(Vetor3d centro, float raio, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m) : centro(centro), raio(raio), K_d(K_d), K_e(K_e), K_a(K_a), m(m) {}

    Vetor3d calcular_iluminacao(Vetor3d Pt, Vetor3d dr, Vetor3d P_F, Vetor3d I_F, Vetor3d I_A) {
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(dr, -1);
        Vetor3d l = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt));
        Vetor3d n = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(Pt, centro));
        float dotproduct_nl = funcoes_auxiliares::Vetor3DotProduct(n, l);
        Vetor3d r = funcoes_auxiliares::Vetor3d_Subtrai(funcoes_auxiliares::Vetor3d_escala(n, 2 * dotproduct_nl), l);
        float dotproduct_vr = funcoes_auxiliares::Vetor3DotProduct(v, r);

        Vetor3d I_d = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K_d, I_F), max(dotproduct_nl, 0));
        Vetor3d I_e = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K_e, I_F), max(pow(dotproduct_vr, m), 0));
        Vetor3d I_a = funcoes_auxiliares::Vetor3d_Multiplica(K_a, I_A);

        Vetor3d I_total = funcoes_auxiliares::Vetor3d_Adiciona(I_d, funcoes_auxiliares::Vetor3d_Adiciona(I_e, I_a));
        return I_total;
    }
};

struct Raio {
    Vetor3d P0;
    Vetor3d dr;

    Raio(Vetor3d P0, Vetor3d dr) : P0(P0), dr(dr) {
    }

    Vetor3d no_ponto(float t) {
        return funcoes_auxiliares::Vetor3d_Adiciona(P0, funcoes_auxiliares::Vetor3d_escala(dr, t));
    }

    float intersecao(Esfera esfera) {
        Vetor3d v = funcoes_auxiliares::Vetor3d_Subtrai(P0, esfera.centro);
        double a = funcoes_auxiliares::Vetor3DotProduct(dr, dr);
        double b = 2 * funcoes_auxiliares::Vetor3DotProduct(dr, v);
        double c = funcoes_auxiliares::Vetor3DotProduct(v, v) - esfera.raio * esfera.raio;
        double delta = b * b - 4 * a * c;
        if(delta < 0.0) {
            return -1.0f;
        }
        float t = (-b - sqrt(delta)) / (2 * a);
        if(t < 0.0) {
            t = (-b + sqrt(delta)) / (2 * a);
        }
        return t;
    }

    float intersecao(Plano plano) {
        Vetor3d v = funcoes_auxiliares::Vetor3d_Subtrai(P0, plano.ponto);
        double a = funcoes_auxiliares::Vetor3DotProduct(dr, plano.normal);
        if(a == 0.0) {
            return -1.0;
        }
        double b = funcoes_auxiliares::Vetor3DotProduct(v, plano.normal);
        return -b / a;
    }
};

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
    Vetor3d Ponto_Superior_Esquerdo = { -W_J * 0.5, W_J * 0.5, -d };
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
                    Vetor3d dr = funcoes_auxiliares::Vetor3dNormalizado(P);
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
                        Vetor3d dr_luz = funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt);
                        Raio raio_luz(Pt, dr_luz);
                        if(raio_luz.intersecao(esfera) < 0.0) {
                            I_total = plano_chao.calcular_iluminacao(Pt, raio.dr, P_F, I_F, I_A);
                        } else {
                            I_total = plano_chao.calcular_iluminacao(Pt, raio.dr, P_F, {0.0f, 0.0f, 0.0f}, I_A);
                        }

                    } else if(t_plano_fundo > 0.0f && (t_plano_fundo < t_esfera || t_esfera < 0.0f) && (t_plano_fundo < t_plano_chao || t_plano_chao < 0.0f)) {
                        Vetor3d Pt = raio.no_ponto(t_plano_fundo);
                        Vetor3d dr_luz = funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt);
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
              (Color){ min(I_total.x * 255.0, 255.0), min(I_total.y * 255.0, 255.0), min(I_total.z * 255.0, 255.0), 255 });
                }
            }

        }
        EndDrawing();
    }

    return 0;
}
