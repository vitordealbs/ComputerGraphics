#include <math.h>
#include <raylib.h>
#include "funcoes_auxiliares.h"

// definicao das dimensoes da janela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// definicao das dimensoes do frame
const float width = 8.0;
const float height = 6.0;

// definicao do numero de linhas do frame
const int lin = 600;

// definicao do numero de colunas do frame
const int col = 800;

// distancia do frame ao olho
float dist_ao_quadro = 2.0;

// raio da esfera
double raio = 6.0;
// centro da esfera
Vetor3d centro_esfera = { 0.0, 0.0, -10.0 };

// vetor representando o material da esfera
const Vetor3d K = { 1, 0.0, 0.0 };

// numero representando o expoente do calculo
// da iluminacao especular
const double alpha = 50.0;

// dados da fonte luminosa pontual
Vetor3d I_F = { 0.7, 0.7, 0.7 };
Vetor3d P_F = { 0.0, 5.0, 0.0 };

// funcao auxiliar que retorna o maximo
// de dois numeros
double
max(double a, double b)
{
    return a + (b - a) * (a < b);
}

// funcao auxiliar que retorna o minimo
// de dois numeros
double min(double a, double b)
{
    return a + (b - a) * (a > b);
}

int main(void) {

    // inicializacao da janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raytracing");
    SetTargetFPS(60);

    // inicializacao do dx e do dy
    double deltinhax = width / col, deltinhay = height / lin;

    // determinacao de quantos pixels correspondem a cada quadrado do frame
    int Deltax = SCREEN_WIDTH / col, Deltay = SCREEN_HEIGHT / lin;

    // loop de renderizacao
    while (!WindowShouldClose()) {

        // codigo para mover a esfera 
        // e para aproximar ou afastar o frame do observador
        if (IsKeyDown(KEY_W)) dist_ao_quadro += 0.05;
        if (IsKeyDown(KEY_S) && dist_ao_quadro > 0.10) dist_ao_quadro -= 0.05;
        if (IsKeyDown(KEY_J)) centro_esfera.y += 0.05;
        if (IsKeyDown(KEY_K)) centro_esfera.y -= 0.05;
        if (IsKeyDown(KEY_H)) centro_esfera.x -= 0.05;
        if (IsKeyDown(KEY_L)) centro_esfera.x += 0.05;

        // definicao do ponto superior esquerdo do frame
        Vetor3d Ponto_Superior_Esquerdo = { -width * 0.5, height * 0.5, -dist_ao_quadro };
        // definicao da coordenada z dos pontos do frame
        double zp = -dist_ao_quadro;
        // definicao do vetor v que vai do centro da esfera ao olho do observador
        Vetor3d v = funcoes_auxiliares::Vetor3d_escala(centro_esfera, -1);

        // inicio do codigo de desenho
        BeginDrawing();
        ClearBackground((Color){ 100, 100, 100, 255 });

        // loop sobre as linhas
        for (int i = 0; i < lin; ++i) {
            // calculo do y do centro dos pontos da linha i
            double yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5 - i*deltinhay;
            // loop sobre as colunas
            for (int j = 0; j < col; ++j) {
                // calculo do x do centro do ponto da coluna j
                double xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5 * deltinhax;
                // construcao do ponto P que representa o centro do quadrado i, j do frame
                Vetor3d P = { xp, yp, zp };
                
                // vetor dr normalizado que aponta do olho do observador
                // ao ponto P
                Vetor3d dr = funcoes_auxiliares::Vetor3dNormalizado(P);

                // calculo dos coeficientes da equacao de intersecao entre a esfera e o raio
                double a = funcoes_auxiliares::Vetor3DotProduct(dr, dr);
                double b = 2 * funcoes_auxiliares::Vetor3DotProduct(dr, v);
                double c = funcoes_auxiliares::Vetor3DotProduct(v, v) - raio * raio;

                // delta da equacao 
                double deltaQuadratico = b * b - 4 * a * c;

                // se o delta for menor que zero, nao ha intersecao 
                if(deltaQuadratico < 0.0) {
                    continue;
                }

                // como a e sempre nao negativo e a raiz qudrada tambem
                // esse e o menor valor de t
                double t = (-b - sqrt(deltaQuadratico)) / (2 * a);
                // se esse t e negativo, tentamos o outro
                if(t < 0.0) {
                    t = (-b + sqrt(deltaQuadratico)) / (2 * a);
                }
                // se esse t tambem e negativo a intersecao ocorreu
                // atras do campo de visao, logo nao e contabilizada
                if(t < 0.0) {
                    continue;
                }

                // calculo do ponto de intersecao a partir de t
                Vetor3d Pt = funcoes_auxiliares::Vetor3d_escala(dr, t);
                // calculo da normal a esfera no ponto de intersecao
                Vetor3d normal = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(Pt, centro_esfera));
                // vetor na direcao inversa de dt
                Vetor3d v_inverso = funcoes_auxiliares::Vetor3d_escala(dr, -1);
                // vetor do ponto de intersecao a fonte de luz
                Vetor3d vetor_luminoso = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(P_F, Pt));
                // vetor representando a direcao do raio refletido
                Vetor3d r = funcoes_auxiliares::Vetor3d_Subtrai(funcoes_auxiliares::Vetor3d_escala(normal, 2 * funcoes_auxiliares::Vetor3DotProduct(normal, vetor_luminoso)), vetor_luminoso);

                // calculo da intensidade da luz difusa
                Vetor3d I_difusa = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K, I_F),
                    max(funcoes_auxiliares::Vetor3DotProduct(vetor_luminoso,normal),
                        0));

                // calculo da intensidade da luz especular
                Vetor3d I_especular = funcoes_auxiliares::Vetor3d_escala(funcoes_auxiliares::Vetor3d_Multiplica(K, I_F), max(pow(funcoes_auxiliares::Vetor3DotProduct(v_inverso,r), alpha), 0));

                // calculo da intensidade da luz total
                Vetor3d I_total = funcoes_auxiliares::Vetor3d_Adiciona(I_difusa, I_especular);

                // desenho do pixel na tela
                DrawRectangle(
          Deltax * j,
          Deltay * i,
          Deltax,
          Deltay,
          (Color){ min(I_total.x * 255.0, 255.0), min(I_total.y * 255.0, 255.0), min(I_total.z * 255.0, 255.0), 255 });
            }
        }

        EndDrawing();
    }

    return 0;
}
