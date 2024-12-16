#ifndef MALHA_H
#define MALHA_H

#include "src/Aresta/Aresta.h"
#include "./src/Triangulo/Triangulo.h"
#include "./funcoes_auxiliares.h" // Certifique-se de incluir Vetor3d
#include <vector>



    struct Malha {
        std::vector<Vetor3d> vertices;       // Lista de vértices
        std::vector<Aresta> arestas;         // Lista de arestas
        std::vector<Triangulo> faces;        // Lista de faces (Triângulos)

        Malha();                             // Construtor padrão
        void inicializar_cubo(  const Vetor3d& centro,
                                float tamanho,
                                const Vetor3d& normal,
                                const Vetor3d& K_d,
                                const Vetor3d& K_e,
                                const Vetor3d& K_a,
                                float m);
        void imprimir();
    };



#endif // MALHA_H