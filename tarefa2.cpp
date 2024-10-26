#include <math.h>
#include <raylib.h>
#include "funcoes_auxiliares.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float width = 8.0;
const float height = 6.0;
const int lin = 600;
const int col = 800;
float dist_ao_quadro = 2.0;
double raio = 6.0;
const Vetor3d K = { 1, 0.0, 0.0 };
const double alpha = 50.0;
Vetor3d I_F = { 0.7, 0.7, 0.7 };
Vetor3d P_F = { 0.0, 5.0, 0.0 };
Vetor3d centro_esfera = { 0.0, 0.0, -10.0 };

double
max(double a, double b)
{
    return a + (b - a) * (a < b);
}

double
min(double a, double b)
{
    return a + (b - a) * (a > b);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raytracing");
    // Shader shader = LoadShader(0, "aula1.fs");
    // RenderTexture2D texture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTargetFPS(60);
    double deltinhax = width / col, deltinhay = height / lin;
    int Deltax = SCREEN_WIDTH / col, Deltay = SCREEN_HEIGHT / lin;

    while (!WindowShouldClose()) {
                /*
        BeginTextureMode(texture);
        {
         ClearBackground(BLACK);
         DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
        }
        EndTextureMode();
           */

        if (IsKeyDown(KEY_W)) dist_ao_quadro += 0.05;
        if (IsKeyDown(KEY_S) && dist_ao_quadro > 0.10) dist_ao_quadro -= 0.05;
        if (IsKeyDown(KEY_J)) centro_esfera.y += 0.05;
        if (IsKeyDown(KEY_K)) centro_esfera.y -= 0.05;
        if (IsKeyDown(KEY_H)) centro_esfera.x -= 0.05;
        if (IsKeyDown(KEY_L)) centro_esfera.x += 0.05;

        Vetor3d Ponto_Superior_Esquerdo = { -width * 0.5, height * 0.5, -dist_ao_quadro };
        double zp = -dist_ao_quadro;
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(centro_esfera, -1);

        BeginDrawing();
        ClearBackground((Color){ 100, 100, 100, 255 });

        for (int i = 0; i < lin; ++i) {
            double yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5 - i*deltinhay;
            for (int j = 0; j < col; ++j) {
                double xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5 * deltinhax;
                Vetor3d P = { xp, yp, zp };
                Vetor3d dist_reflexao = P;

                double a = funcoes_auxiliares::Vetor3DotProduct(dist_reflexao, dist_reflexao);
                double b = funcoes_auxiliares::Vetor3DotProduct(dist_reflexao, v);
                double c = funcoes_auxiliares::Vetor3DotProduct(v, v) - raio * raio;
                double deltaQuadratico = b * b - a * c;

                if (deltaQuadratico >= 0.0) {
                    double t = (-b - sqrt(deltaQuadratico)) / a;
                    Vetor3d Pt = funcoes_auxiliares::Vetor3d_escala(dist_reflexao, t);
                    double distancia_escalar = funcoes_auxiliares::Vetor3_tamanho(Pt);
                    Vetor3d normal = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(Pt, centro_esfera));
                    Vetor3d v_inverso = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3dNormalizado(dist_reflexao), -1);
                    Vetor3d vetor_luminoso = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt));


                    double proj_luz_normal = funcoes_auxiliares::Vetor3DotProduct(normal, vetor_luminoso);



                    Vetor3d proj_de_luz = funcoes_auxiliares::Vetor3d_escala(normal, proj_luz_normal);
                    Vetor3d r =
                        funcoes_auxiliares::Vetor3d_Adiciona(proj_de_luz,
                        funcoes_auxiliares::Vetor3d_escala
                        (funcoes_auxiliares::Vetor3d_Subtrai(vetor_luminoso, proj_de_luz)
                        , -1));


                    Vetor3d I_difusa = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K, I_F),
                        max(funcoes_auxiliares::Vetor3DotProduct(vetor_luminoso,normal),
                            0));

                    Vetor3d I_especular = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K, I_F), max(pow(funcoes_auxiliares::Vetor3DotProduct(v_inverso,r), alpha), 0));


                    Vetor3d I_total = funcoes_auxiliares::Vetor3d_Adiciona(I_difusa, I_especular);

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
