#include <math.h>
#include <raylib.h>
#include "funcoes_auxiliares.h"

// definicao das dimensoes da janela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// definicao das dimensoes do frame
const float wJanela = 8.0;
const float hJanela = 6.0;

// definicao do numero de linhas do frame
const int nLin = 600;

// definicao do numero de colunas do frame
const int nCol = 800;

// distancia do frame ao olho
float dJanela = 2.0;

// raio da esfera
float rEsfera = 6.0;
// centro da esfera
Vetor3d centro_esfera = { 0.0, 0.0, -(dJanela+rEsfera) };

// cor da esfera
Vetor3d esfColor = {255.0, 0.0, 0.0};

// cor do background
Vetor3d bgColor = {100.0, 100.0, 100.0};

int
main(void)
{
    // inicializacao da janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tarefa 01");
    SetTargetFPS(60);

    // inicializacao do dx e do dy
    double deltinhax = wJanela / nCol, deltinhay = hJanela / nLin;

    // determinacao de quantos pixels correspondem a cada quadrado do frame
    int Deltax = SCREEN_WIDTH / nCol, Deltay = SCREEN_HEIGHT / nLin;

    // loop de renderizacao
    while (!WindowShouldClose()) {

        // definicao do ponto superior esquerdo do frame
        Vetor3d PSE = { -wJanela * 0.5, hJanela * 0.5, -dJanela };
        // definicao da coordenada z dos pontos do frame
        float zp = -dJanela;
        // definicao do vetor v que vai do centro da esfera ao olho do observador
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(centro_esfera, -1);

        // inicio do codigo de desenho
        BeginDrawing();
        {
            ClearBackground(BLACK);

            // loop sobre as linhas
            for (int i = 0; i < nLin; ++i) {
                // calculo do y do centro dos pontos da linha i
                float yp = PSE.y - deltinhay * 0.5 - i * deltinhay;
                // loop sobre as colunas
                for (int j = 0; j < nCol; ++j) {
                    // calculo do x do centro do ponto da coluna j
                    float xp = PSE.x + deltinhax * 0.5 + j * deltinhax;
                    // construcao do ponto P que representa o centro do quadrado i, j do frame
                    Vetor3d P = { xp, yp, zp };
                    // vetor dr normalizado que aponta do olho do observador
                    // ao ponto P
                    Vetor3d dr = funcoes_auxiliares::Vetor3dNormalizado(P);
                    
                    // calculo dos coeficientes da equacao de intersecao entre a esfera e o raio
                    double a = funcoes_auxiliares::Vetor3DotProduct(dr, dr);
                    double b = funcoes_auxiliares::Vetor3DotProduct(dr, v);
                    double c = funcoes_auxiliares::Vetor3DotProduct(v, v) - rEsfera * rEsfera;

                    // delta da equacao 
                    double delta = b * b - a * c;
                    // se o delta for menor que zero, nao ha intersecao 
                    if(delta < 0.0) {
                        DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, (Color) { (unsigned char)bgColor.x, (unsigned char)bgColor.y, (unsigned char)bgColor.z, 255 });
                        continue;
                    }

                    // como a e sempre nao negativo e a raiz qudrada tambem
                    // esse e o menor valor de t
                    double t = (-b - sqrt(delta)) / a;
                    // se esse t e negativo, tentamos o outro
                    if(t < 0.0) {
                        t = (-b + sqrt(delta)) / a;
                    }
                    // se esse t tambem e negativo a intersecao ocorreu
                    // atras do campo de visao, logo nao e contabilizada
                    if (t < 0.0) {
                        DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, (Color) { (unsigned char)bgColor.x, (unsigned char)bgColor.y, (unsigned char)bgColor.z, 255 });
                        continue;
                    }

                    // caso chegemos a esse ponto, ou intersecao
                    // logo, colorimos o pixel com a cor da esfera
                    DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, (Color) { (unsigned char)esfColor.x, (unsigned char)esfColor.y, (unsigned char)esfColor.z, 255 });
                }
            }

        }
        EndDrawing();
    }

    return 0;
}
