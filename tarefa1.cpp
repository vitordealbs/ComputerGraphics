#include <math.h>
#include <raylib.h>
#include "funcoes_auxiliares.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float wJanela = 8.0;
const float hJanela = 6.0;
const int nLin = 600;
const int nCol = 800;
float dJanela = 2.0;
float rEsfera = 6.0;
Vetor3d centro_esfera = { 0.0, 0.0, dJanela+rEsfera };

int
main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raytracing");
    // Shader shader = LoadShader(0, "aula1.fs");
    // RenderTexture2D texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(60);

    double deltinhax = wJanela / nCol, deltinhay = hJanela / nLin;
    int Deltax = SCREEN_WIDTH / nCol, Deltay = SCREEN_HEIGHT / nLin;

    while (!WindowShouldClose()) {
        /*
    BeginTextureMode(texture);
    {
      ClearBackground(BLACK);
      DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    }
    EndTextureMode();
        */

        if (IsKeyDown(KEY_W)) {
            dJanela += 0.05;
        } else if (IsKeyDown(KEY_S) && dJanela > 0.10) {
            dJanela -= 0.05;
        } else if (IsKeyDown(KEY_J)) {
            centro_esfera.y += 0.05;
        } else if (IsKeyDown(KEY_K)) {
            centro_esfera.y -= 0.05;
        } else if (IsKeyDown(KEY_H)) {
            centro_esfera.x -= 0.05;
        } else if (IsKeyDown(KEY_L)) {
            centro_esfera.x += 0.05;
        }

        Vetor3d PSE = { -wJanela * 0.5, hJanela * 0.5, -dJanela };
        double zp = -dJanela;
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(centro_esfera, -1);

        BeginDrawing();
        {
            ClearBackground(GRAY);

            for (int i = 0; i < nLin; ++i) {
                double yp = PSE.y - deltinhay * 0.5 - i * deltinhay;
                for (int j = 0; j < nCol; ++j) {
                    double xp = PSE.x + deltinhax * 0.5 + j * deltinhax;
                    Vetor3d P = { xp, yp, zp };
                    Vetor3d dr = P;
                    double a = funcoes_auxiliares::Vetor3DotProduct(dr, dr);
                    double b = funcoes_auxiliares::Vetor3DotProduct(dr, v);
                    double c = funcoes_auxiliares::Vetor3DotProduct(v, v) - rEsfera * rEsfera;
                    if (b * b - a * c >= 0.0) {
                        DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, RED);
                    }
                }
            }

            /*
                  BeginShaderMode(shader);
                  DrawTexture(texture.texture, 0, 0, WHITE);
                  EndShaderMode();
                      */
        }
        EndDrawing();
    }

    return 0;
}