// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares.h"
#include <cmath> // Para sqrtf()

namespace funcoes_auxiliares {

    Vetor3d Auxiliares::Vetor3d_escala (Vetor3d v, float scalar) {
        Vetor3d resultado = { v.x * scalar, v.y * scalar, v.z * scalar };
        return resultado;
    }

    float Auxiliares::Vetor3DotProduct(Vetor3d v1, Vetor3d v2) {
        float result = (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
        return result;
    }

    float Auxiliares::Vetor3_tamanho(const Vetor3d v) {
        float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        return result;
    }

    Vetor3d Auxiliares::Vetor3dNormalizado(Vetor3d v) {
        Vetor3d result = v;
        float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        if (length == 0.0f) length = 1.0f;
        float ilength = 1.0f / length;

        result.x *= ilength;
        result.y *= ilength;
        result.z *= ilength;

        return result;
    }

    Vetor3d Auxiliares::Vetor3d_Subtrai(Vetor3d v1, Vetor3d v2) {
        Vetor3d result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
        return result;
    }

    Vetor3d Auxiliares::Vetor3d_Adiciona(Vetor3d v1, Vetor3d v2) {
        Vetor3d result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
        return result;
    }

    Vetor3d Auxiliares::Vetor3d_Multiplica(Vetor3d v1, Vetor3d v2) {
        Vetor3d result = { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
        return result;
    }
}
