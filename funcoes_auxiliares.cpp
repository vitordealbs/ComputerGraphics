//
// Created by Vitor de Albuquerque on 25/10/2024.
//

#include "funcoes_auxiliares.h"
#include <math.h>
#include <iostream>

Raio construir2Pontos(Vetor3d P0, Vetor3d P) {
    Vetor3d dr = funcoes_auxiliares::Vetor3dNormalizado(funcoes_auxiliares::Vetor3d_Subtrai(P, P0));
    return Raio(P0, dr);
}

Raio::Raio(Vetor3d P0, Vetor3d dr) : P0(P0), dr(dr) {}

Esfera::Esfera(Vetor3d centro, float raio) : centro(centro), raio(raio) {}

Vetor3d funcoes_auxiliares::Vetor3d_escala (Vetor3d v, float scalar)
{
    Vetor3d resultado = { v.x*scalar, v.y*scalar, v.z*scalar };

    return resultado;
}


float funcoes_auxiliares::Vetor3DotProduct(Vetor3d v1, Vetor3d v2)
{
    float result = (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);

    return result;
}


float funcoes_auxiliares::Vetor3_tamanho(const Vetor3d v)
{
    float result = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);

    return result;
}


Vetor3d funcoes_auxiliares::Vetor3dNormalizado(Vetor3d v)
{
    Vetor3d result = v;

    float length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length == 0.0f) length = 1.0f;
    float ilength = 1.0f/length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;

    return result;
}

Vetor3d funcoes_auxiliares::Vetor3d_Subtrai(Vetor3d v1, Vetor3d v2)
{
    Vetor3d result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };

    return result;
}

Vetor3d funcoes_auxiliares::Vetor3d_Adiciona(Vetor3d v1, Vetor3d v2)
{
    Vetor3d result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };

    return result;
}

Vetor3d funcoes_auxiliares::Vetor3d_Multiplica(Vetor3d v1, Vetor3d v2)
{
    Vetor3d result = { v1.x*v2.x, v1.y*v2.y, v1.z*v2.z };

    return result;
}
