// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

namespace funcoes_auxiliares {
    // Definição da estrutura Vetor3d
    struct Vetor3d {
        float x; // Componente x
        float y; // Componente y
        float z; // Componente z

        float dot_product(Vetor3d vetor);
        float tamanho();
        Vetor3d normalizado();

    };
//Métodos auxiliares de operação
    Vetor3d operator*(Vetor3d vetor, float escalar);
    Vetor3d operator*(float escalar, Vetor3d vetor);
    Vetor3d operator*(Vetor3d vetor1, Vetor3d vetor2);
    Vetor3d operator+(Vetor3d vetor1, Vetor3d vetor2);
    Vetor3d operator-(Vetor3d vetor1, Vetor3d vetor2);

}

#endif // FUNCOES_AUXILIARES_H
