// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares.h"
#include <cmath> // Para sqrtf()

    namespace funcoes_auxiliares {

        float Vetor3d::dot_product(Vetor3d vetor) {
            return x * vetor.x + y * vetor.y + z * vetor.z;
        }

        float Vetor3d::tamanho() {
            return sqrtf(x * x + y * y + z * z);
        }

        Vetor3d Vetor3d::normalizado() {
            float tam = tamanho();
            Vetor3d resultado = {x / tam, y / tam, z / tam };
            return resultado;
        }

        Vetor3d operator*(Vetor3d vetor, float escalar) {
            Vetor3d resultado = {vetor.x * escalar, vetor.y * escalar, vetor.z * escalar};
            return resultado;
        }

        Vetor3d operator*(float escalar, Vetor3d vetor) {
            Vetor3d resultado = {vetor.x * escalar, vetor.y * escalar, vetor.z * escalar};
            return resultado;
        }

        Vetor3d operator*(Vetor3d vetor1, Vetor3d vetor2) {
            Vetor3d resultado = {vetor1.x * vetor2.x, vetor1.y * vetor2.y, vetor1.z * vetor2.z};
            return resultado;
        }

        Vetor3d operator+(Vetor3d vetor1, Vetor3d vetor2) {
            Vetor3d resultado = {vetor1.x + vetor2.x, vetor1.y + vetor2.y, vetor1.z + vetor2.z};
            return resultado;
        }

        Vetor3d operator-(Vetor3d vetor1, Vetor3d vetor2) {
            Vetor3d resultado = {vetor1.x - vetor2.x, vetor1.y - vetor2.y, vetor1.z - vetor2.z};
            return resultado;
        }

        /*

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
        */
}
