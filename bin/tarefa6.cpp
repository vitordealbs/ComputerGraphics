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