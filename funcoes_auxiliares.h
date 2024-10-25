//
// Created by Vitor de Albuquerque on 25/10/2024.
//

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

// Definição da estrutura Vetor3d fora da classe
struct Vetor3d {
    float x; // componente x
    float y; // componente y
    float z; // componente z
};

// Declaração da classe com métodos auxiliares
class funcoes_auxiliares {
public:
    static Vetor3d Vetor3d_escala(Vetor3d v, float scalar);
    static float Vetor3DotProduct(Vetor3d v1, Vetor3d v2);
    static float Vetor3_tamanho(Vetor3d v);
    static Vetor3d Vetor3dNormalizado(Vetor3d v);
    static Vetor3d Vetor3d_Subtrai(Vetor3d v1, Vetor3d v2);
    static Vetor3d Vetor3d_Adiciona(Vetor3d v1, Vetor3d v2);
    static Vetor3d Vetor3d_Multiplica(Vetor3d v1, Vetor3d v2);
};

#endif //FUNCOES_AUXILIARES_H
