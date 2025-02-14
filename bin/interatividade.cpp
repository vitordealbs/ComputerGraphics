#include <cstdio>
#include <math.h>

#include <raylib.h>
#include <raymath.h>

#include <string>
#include <vector>

#include "./src/Cilindro/Cilindro.h"
#include "./src/Circulo/Circulo.h"
#include "./src/Cone/Cone.h"
#include "./src/Esfera/Esfera.h"
#include "./src/Iluminacao/Iluminacao.h"
#include "./src/Material/Material.h"
#include "./src/Objeto/Objeto.h"
#include "./src/Plano/Plano.h"
#include "./src/Raio/Raio.h"
#include "./src/Triangulo/Triangulo.h"
#include "funcoes_auxiliares.h"
using namespace funcoes_auxiliares;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
const Color BACKGROUND_COLOR = { 44, 44, 44, 255 };
const Color TEXTBOX_COLOR = { 64, 64, 64, 255 };
const Color BUTTON_COLOR = { 54, 54, 54, 255 };
const float BUTTON_FONTSIZE = 20.0f;
const float TEXTBOX_PADDING = 2.0f;
const float LABEL_MARGIN = 4.0f;

struct TextBox
{
  Rectangle rect;
  std::string label;
  char texto[10] = { 0 };
  size_t capacidade = 9;
  size_t cursor = 0;
  float* parametro = nullptr;

  TextBox(std::string label, int x, int y, int width, int height, float *parametro)
    : label(label), parametro(parametro)
  {
    rect = (Rectangle){ (float)x, (float)y, (float)width, (float)height };
  }

  TextBox(std::string label, Rectangle rect, float *parametro)
    : label(label)
    , rect(rect)
    , parametro(parametro)
  {
  }

  void desenhar(Font font)
  {
    float font_size = rect.height - 2 * TEXTBOX_PADDING;
    float label_height = rect.height;
    Vector2 label_pos = { rect.x, rect.y };
    DrawTextEx(font, label.c_str(), label_pos, font_size, 3.0f, WHITE);
    Rectangle box_rect = {
      rect.x, rect.y + label_height + LABEL_MARGIN, rect.width, rect.height
    };
    DrawRectangleRec(box_rect, TEXTBOX_COLOR);
    Vector2 text_pos = { box_rect.x + TEXTBOX_PADDING,
                         box_rect.y + TEXTBOX_PADDING };
    DrawTextEx(font, texto, text_pos, font_size, 3.0f, WHITE);
  }

  bool intersecao(Vector2 ponto)
  {
    float label_height = rect.height;
    Rectangle box_rect = {
      rect.x, rect.y + label_height + LABEL_MARGIN, rect.width, rect.height
    };
    return CheckCollisionPointRec(ponto, box_rect);
  }

  void atualizar(int key, char key_char)
  {
    if (key == KEY_BACKSPACE) {
      if (cursor > 0) {
        texto[--cursor] = '\0';
      }
    } else if (key != 0 && cursor < capacidade && key != KEY_LEFT_SHIFT) {
      texto[cursor++] = key_char;
    }
  }
  
  void atualizar_parametro()
  {
    TraceLog(LOG_INFO, "parametro antigo %f", *parametro);
    sscanf(texto, "%f", parametro);
    TraceLog(LOG_INFO, "parametro novo %f", *parametro);
  }
};

struct Button
{
  std::string label;
  Rectangle rect;

  Button(std::string label, Rectangle rect)
    : label(label)
    , rect(rect)
  {
  }

  void desenhar(Font font)
  {
    DrawRectangleRec(rect, BUTTON_COLOR);
    Vector2 text_offset =
      MeasureTextEx(font, label.c_str(), BUTTON_FONTSIZE, 3.0f);
    Vector2 rect_center = { rect.x + 0.5f * rect.width,
                            rect.y + 0.5f * rect.height };
    Vector2 text_pos = Vector2Subtract(rect_center, Vector2Scale(text_offset, 0.5));
    DrawTextEx(font, label.c_str(), text_pos, BUTTON_FONTSIZE, 3.0f, WHITE);
  }

  bool intersecao(Vector2 ponto) { return CheckCollisionPointRec(ponto, rect); }
};

struct ScrollPanel
{};

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

double deltinhax = W_J / nCol, deltinhay = H_J / nLin;
int Deltax = W_C / nCol, Deltay = H_C / nLin;
Vetor3d Ponto_Superior_Esquerdo = { -W_J * 0.5f, W_J * 0.5f, -d };
float zp = -d;
Vetor3d P0 = { 0.0f, 0.0f, 0.0f };

// definicao da esfera da cena
Vetor3d K_d_esfera = { 0.7, 0.2, 0.2 };
Vetor3d K_e_esfera = { 0.7, 0.2, 0.2 };
Vetor3d K_a_esfera = { 0.7, 0.2, 0.2 };
float R = 40.0f;
float m_esfera = 10;
Esfera esfera({ 0.0f, 0.0f, -100.0f },
              R,
              K_d_esfera,
              K_e_esfera,
              K_a_esfera,
              m_esfera);

// definicao do plano do chao
Vetor3d K_d_plano_chao = { 0.2f, 0.7f, 0.2f };
Vetor3d K_e_plano_chao = { 0.0f, 0.0f, 0.0f };
Vetor3d K_a_plano_chao = { 0.2f, 0.7f, 0.2f };
float m_plano_chao = 1;
Plano plano_chao({ 0.0f, -R, 0.0f },
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

// definicao do cilindro
Vetor3d K_d_cilindro = { 0.2, 0.3, 0.8 };
Vetor3d K_e_cilindro = K_d_cilindro;
Vetor3d K_a_cilindro = K_d_cilindro;
float m_cilindro = 1;
Vetor3d dir_cilindro = { -1.0f / sqrtf(3.0),
                         1.0f / sqrtf(3.0f),
                         1.0f / sqrtf(3.0) };
Vetor3d centro_cilindro = { 0.0f, 0.0f, -100.0f };
Cilindro cilindro({ 0.0f, 0.0f, -100.0f },
                  R / 3.0f,
                  1.7f * R,
                  dir_cilindro,
                  K_d_cilindro,
                  K_e_cilindro,
                  K_a_cilindro,
                  m_cilindro);
Circulo topo_cilindro(dir_cilindro * (1.4f * R) + centro_cilindro,
                      R / 3.0f,
                      dir_cilindro,
                      K_d_cilindro,
                      K_e_cilindro,
                      K_a_cilindro,
                      m_cilindro);
Circulo base_cilindro(centro_cilindro,
                      R / 3.0f,
                      -1.0f * dir_cilindro,
                      K_d_cilindro,
                      K_e_cilindro,
                      K_a_cilindro,
                      m_cilindro);

// definicao do cone
Vetor3d K_d_cone = { 0.8, 0.3, 0.2 };
Vetor3d K_e_cone = K_d_cone;
Vetor3d K_a_cone = K_d_cone;
float m_cone = 1;
Vetor3d centro_cone = topo_cilindro.centro;
Vetor3d dir_cone = cilindro.direcao;
Cone cone(centro_cone,
          R * 1,
          (R * 1.5f) / 3.0f,
          dir_cone,
          K_d_cone,
          K_e_cone,
          K_a_cone,
          m_cone);
Circulo base_cone(centro_cone,
                  R / 3.0f,
                  -1.0f * dir_cone,
                  K_d_cone,
                  K_e_cone,
                  K_a_cone,
                  m_cone);

// definicao da fonte luminosa
Vetor3d I_F = { 0.7f, 0.7f, 0.7f };
Vetor3d P_F = { 0.0f, 60.0f, -30.0f };

// definicao da iluminacao ambiente
Vetor3d I_A = { 0.3f, 0.3f, 0.3f };

std::vector<Objeto> objetos = { Objeto(plano_fundo),   Objeto(plano_chao),
                                Objeto(esfera),        Objeto(cilindro),
                                Objeto(topo_cilindro), Objeto(base_cilindro),
                                Objeto(cone),          Objeto(base_cone) };

void
renderizar(RenderTexture2D tela)
{

  BeginTextureMode(tela);
  {
    ClearBackground(BLACK);

    for (int i = 0; i < nLin; ++i) {
      float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5f - i * deltinhay;
      for (int j = 0; j < nCol; ++j) {
        float xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5f * deltinhax;
        Vetor3d P = { xp, yp, zp };
        Vetor3d dr = P.normalizado();
        Raio raio(P0, dr);
        auto [t, objeto] = calcular_intersecao(raio, objetos);
        Vetor3d I_total = I_A;
        Vetor3d Pt = raio.no_ponto(t);
        Vetor3d dr_luz = (P_F - Pt).normalizado();
        Raio raio_luz(Pt, dr_luz);
        auto [t_luz, _] = calcular_intersecao(raio_luz, objetos, objeto);
        if (t_luz < 0.0 || t_luz > (P_F - Pt).tamanho()) {
          I_total = iluminacao::modelo_phong(Pt,
                                             raio.dr,
                                             objetos[objeto].normal(Pt),
                                             { P_F, I_F },
                                             I_A,
                                             objetos[objeto].material);
        } else {
          I_total = iluminacao::luz_ambiente(I_A, objetos[objeto].material.K_a);
        }

        DrawRectangle(
          Deltax * j,
          Deltay * i,
          Deltax,
          Deltay,
          (Color){ static_cast<unsigned char>(min(I_total.x * 255.0f, 255.0f)),
                   static_cast<unsigned char>(min(I_total.y * 255.0f, 255.0f)),
                   static_cast<unsigned char>(min(I_total.z * 255.0f, 255.0f)),
                   255 });
      }
    }
  }
  EndTextureMode();
}

int
main(void)
{

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Interatividade");
  SetTargetFPS(60);

  Font font = GetFontDefault();

  int objeto_selecionado = -1;

  RenderTexture2D tela = LoadRenderTexture(W_C, H_C);

  renderizar(tela);

  TextBox caixa1("I.r", (Rectangle){ 520.0f, 20.0f, 260.0f, 20.0f }, &I_F.x);
  TextBox caixa2("I.g", (Rectangle){ 520.0f, 80.0f, 260.0f, 20.0f }, &I_F.y);
  TextBox caixa3("I.b", (Rectangle){ 520.0f, 140.0f, 260.0f, 20.0f }, &I_F.z);
  std::vector<TextBox> caixas;
  caixas.push_back(caixa1);
  caixas.push_back(caixa2);
  caixas.push_back(caixa3);
  int caixa_selecionada = -1;

  Button btn_atualizar("atualizar",
                       (Rectangle){ 520.0f, 200.0f, 260.0f, 30.0f });

  while (!WindowShouldClose()) {

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      caixa_selecionada = -1;
      if (mouse.x < W_C && mouse.y < H_C) {
        int x_pos = mouse.x, y_pos = mouse.y;
        float yp =
          Ponto_Superior_Esquerdo.y - deltinhay * 0.5f - y_pos * deltinhay;
        float xp =
          Ponto_Superior_Esquerdo.x + deltinhax * x_pos + 0.5f * deltinhax;
        Vetor3d P = { xp, yp, zp };
        Vetor3d dr = P.normalizado();
        Raio raio(P0, dr);
        auto [t, objeto] = calcular_intersecao(raio, objetos);
        if (t > 0.0f)
          objeto_selecionado = objeto;
        TraceLog(LOG_INFO, "objeto_selecionado = %d", objeto_selecionado);
      } else {
        for (int i = 0; i < caixas.size(); ++i) {
          TextBox& caixa = caixas[i];
          if (caixa.intersecao(mouse)) {
            caixa_selecionada = i;
          }
        }
        if(caixa_selecionada < 0 && btn_atualizar.intersecao(mouse)) {
          for (int i = 0; i < caixas.size(); ++i) {
            caixas[i].atualizar_parametro();
          }
          renderizar(tela);
        }
      }
    }

    if (caixa_selecionada >= 0) {
      TextBox* caixa = &caixas[caixa_selecionada];
      int key = GetKeyPressed();
      char key_char = GetCharPressed();
      caixa->atualizar(key, key_char);
    }

    BeginDrawing();
    {
      ClearBackground(BACKGROUND_COLOR);
      DrawTextureRec(
        tela.texture, { 0.0f, 0.0f, W_C, -H_C }, { 0.0f, 0.0f }, WHITE);
      for (TextBox& caixa : caixas) {
        caixa.desenhar(font);
      }
      btn_atualizar.desenhar(font);
    }
    EndDrawing();
  }

  UnloadRenderTexture(tela);

  return 0;
}
