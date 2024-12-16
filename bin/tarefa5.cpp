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

using namespace funcoes_auxiliares;



std::pair<float, int>
calcular_intersecao(Raio raio, std::vector<Objeto> objetos, int excluir = -1)
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
Vetor3d K_d_triangulo = { 0.7, 0.2, 0.2 };
Vetor3d K_e_triangulo = { 0.7, 0.2, 0.2 };
Vetor3d K_a_triangulo = { 0.7, 0.2, 0.2 };
float m_triangulo = 10;
Triangulo triangulo({ -40.0f, -40.0f, -100.0f },
                    { 40.0f, -40.0f, -100.0f },
                    { -40.0f, 40.0f, -100.0f },
                    K_d_triangulo,
                    K_e_triangulo,
                    K_a_triangulo,
                    m_triangulo);

// definicao do plano do chao
Vetor3d K_d_plano_chao = { 0.2f, 0.7f, 0.2f };
Vetor3d K_e_plano_chao = { 0.0f, 0.0f, 0.0f };
Vetor3d K_a_plano_chao = { 0.2f, 0.7f, 0.2f };
float m_plano_chao = 1;
Plano plano_chao({ 0.0f, -40.0f, 0.0f },
                 { 0.0f, 1.0f, 0.0f },
                 K_d_plano_chao,
                 K_e_plano_chao,
                 K_a_plano_chao,
                 m_plano_chao);

// definicao do plano de fundo
Vetor3d K_d_plano_fundo = { 0.3f, 0.3f, 0.7f };
Vetor3d K_e_plano_fundo = { 0.0f, 0.0f, 0.0f };
Vetor3d K_a_plano_fundo = { 0.3f, 0.3f, 0.7f };
float m_plano_fundo = 1;
Plano plano_fundo({ 0.0f, 0.0f, -200.0f },
                  { 0.0f, 0.0f, 1.0f },
                  K_d_plano_fundo,
                  K_e_plano_fundo,
                  K_a_plano_fundo,
                  m_plano_fundo);

// definicao da fonte luminosa
Vetor3d I_F = { 0.7f, 0.7f, 0.7f };
Vetor3d P_F = { 0.0f, 60.0f, -30.0f };

// definicao da iluminacao ambiente
Vetor3d I_A = { 0.3f, 0.3f, 0.3f };

std::vector<Objeto> objetos = { Objeto(triangulo),
                                Objeto(plano_chao),
                                Objeto(plano_fundo) };

int
main(void)
{
  InitWindow(W_C, H_C, "Tarefa 04");
  SetTargetFPS(60);

  Image textura_madeira = LoadImage("../cmake-build-default/madeira.png");
  Color* pixels_textura_madeira = LoadImageColors(textura_madeira);

  double deltinhax = W_J / nCol, deltinhay = H_J / nLin;
  int Deltax = W_C / nCol, Deltay = H_C / nLin;
  Vetor3d Ponto_Superior_Esquerdo = { -W_J * 0.5f, W_J * 0.5f, -d };
  float zp = -d;
  Vetor3d P0 = { 0.0f, 0.0f, 0.0f };

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);

      for (int i = 0; i < nLin; ++i) {
        float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5 - i * deltinhay;
        for (int j = 0; j < nCol; ++j) {
          float xp =
            Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5 * deltinhax;
          Vetor3d P = { xp, yp, zp };
          Vetor3d dr = P.normalizado();
          Raio raio(P0, dr);
          // auto [t, objeto] = calcular_intersecao(raio, objetos);
          float t = raio.intersecao(triangulo);
          Vetor3d I_total = I_A;
          if (t > 0.0f) {
            Vetor3d Pt = raio.no_ponto(t);
            Vetor3d v = Pt - triangulo.P0;
            Vetor3d l1 = triangulo.lado1;
            Vetor3d l2 = triangulo.lado2;
            float det = l1.x * l2.y - l1.y * l2.x;
            if (det == 0.0f)
              det = 1.0f;
            float a = (v.x * l2.y - v.y * l2.x) / det;
            float b = (v.y * l1.x - v.x * l1.y) / det;
            int image_x = (float)textura_madeira.width * a;
            int image_y = (float)textura_madeira.height * (1.0f - b);
            Color pixel =
              pixels_textura_madeira[textura_madeira.width * image_y + image_x];
            Vetor3d K_d_textura = { pixel.r / 255.0f,
                                    pixel.g / 255.0f,
                                    pixel.b / 255.0f };
            Vetor3d K_e_textura = K_d_textura;
            Vetor3d K_a_textura = K_d_textura;
            float m_textura = 1.0f;
            MaterialSimples material = {
              K_d_textura, K_e_textura, K_a_textura, m_textura
            };
            I_total = iluminacao::modelo_phong(
              Pt, raio.dr, triangulo.normal, { P_F, I_F }, I_A, material);
          }
          /*
          Vetor3d Pt = raio.no_ponto(t);
          Vetor3d dr_luz = (P_F - Pt).normalizado();
          Raio raio_luz(Pt, dr_luz);
          auto [t_luz, _] = calcular_intersecao(raio_luz, objetos, objeto);
          if(t_luz < 0.0 || t_luz > (P_F - Pt).tamanho()) {
              I_total = iluminacao::modelo_phong(Pt, raio.dr,
          objetos[objeto].normal(Pt), {P_F, I_F}, I_A,
          objetos[objeto].material); } else { I_total =
          iluminacao::luz_ambiente(I_A, objetos[objeto].material.K_a);
          }
          */

          DrawRectangle(
            Deltax * j,
            Deltay * i,
            Deltax,
            Deltay,
            (Color){
              static_cast<unsigned char>(min(I_total.x * 255.0f, 255.0f)),
              static_cast<unsigned char>(min(I_total.y * 255.0f, 255.0f)),
              static_cast<unsigned char>(min(I_total.z * 255.0f, 255.0f)),
              255 });
        }
      }
    }
    EndDrawing();
  }

  UnloadImageColors(pixels_textura_madeira);
  UnloadImage(textura_madeira);

  return 0;
}