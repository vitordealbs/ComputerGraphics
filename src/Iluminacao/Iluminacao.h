//
// Created by Vitor de Albuquerque on 16/12/2024.
//

#ifndef ILUMINACAO_H
#define ILUMINACAO_H
#include "funcoes_auxiliares.h"
#include "./src/Raio/Raio.h"
using namespace funcoes_auxiliares;


namespace iluminacao {
    Vetor3d
    modelo_phong(Vetor3d Pt,
                 Vetor3d dr,
                 Vetor3d n,
                 FontePontual fonte,
                 Vetor3d I_A,
                 MaterialSimples material);
    Vetor3d
    luz_ambiente(Vetor3d I_A, Vetor3d K_a);
}



#endif //ILUMINACAO_H
