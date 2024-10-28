// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

namespace funcoes_auxiliares {
    // Definição da estrutura Vetor3d
    struct Vetor3d {
        float x; // Componente x
        float y; // Componente y
        float z; // Componente z
    };

    // Declaração da classe com métodos auxiliares
    class Auxiliares {
    public:
        static Vetor3d Vetor3d_escala(Vetor3d v, float scalar);
        static float Vetor3DotProduct(Vetor3d v1, Vetor3d v2);
        static float Vetor3_tamanho(Vetor3d v);
        static Vetor3d Vetor3dNormalizado(Vetor3d v);
        static Vetor3d Vetor3d_Subtrai(Vetor3d v1, Vetor3d v2);
        static Vetor3d Vetor3d_Adiciona(Vetor3d v1, Vetor3d v2);
        static Vetor3d Vetor3d_Multiplica(Vetor3d v1, Vetor3d v2);
    };
}

#endif // FUNCOES_AUXILIARES_H
