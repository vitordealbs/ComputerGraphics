// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_DE_MODELACAO_H
#define FUNCOES_AUXILIARES_DE_MODELACAO_H

#include "funcoes_auxiliares.h" // Incluindo o arquivo de operações vetoriais
using namespace funcoes_auxiliares;

    namespace Auxiliares_de_modelacao {

    struct Plano; // Declaração antecipada de Plano

    struct Esfera {
        Vetor3d centro;
        float raio;
        Vetor3d K_d;
        Vetor3d K_e;
        Vetor3d K_a;
        float m;

        Esfera(Vetor3d centro, float raio, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m);
        Vetor3d calcular_iluminacao(Vetor3d Pt, Vetor3d dr, Vetor3d P_F, Vetor3d I_F, Vetor3d I_A);
    };

        struct Plano {
            Vetor3d ponto;
            Vetor3d normal;
            Vetor3d K_d;
            Vetor3d K_e;
            Vetor3d K_a;
            float m;

            // Construtor correto para inicializar as propriedades do plano
            Plano(Vetor3d ponto, Vetor3d normal, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m);
            Vetor3d calcular_iluminacao(Vetor3d ponto, Vetor3d normal, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a);
        };


    struct Raio {
        Vetor3d P0;
        Vetor3d dr;

        Raio(Vetor3d P0, Vetor3d dr);
        Vetor3d no_ponto(float t);
        float intersecao(Esfera esfera);
        float intersecao(Plano plano); // Função de intersecção com Plano
    };

    // Funções max e min
    double max(double a, double b);
    double min(double a, double b);

}

#endif // FUNCOES_AUXILIARES_DE_MODELACAO_H
