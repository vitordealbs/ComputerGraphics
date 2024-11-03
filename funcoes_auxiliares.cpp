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

}
