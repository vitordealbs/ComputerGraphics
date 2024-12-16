#ifndef ESFERA_H
#define ESFERA_H

#include "./../Material/Material.h"
#include "./../Raio/Raio.h"
#include "funcoes_auxiliares.h"

using namespace funcoes_auxiliares;
struct Esfera;

	struct Esfera
	{
  	Vetor3d centro;
  	float raio;
  	Vetor3d K_d;
  	Vetor3d K_e;
  	Vetor3d K_a;
  	float m;
	Esfera() : centro(), raio(0), K_d(), K_e(), K_a(), m(0) {}

 	 Esfera(Vetor3d centro,
         	float raio,
         	Vetor3d K_d,
        	 Vetor3d K_e,
         	Vetor3d K_a,
         	float m);

  	Vetor3d calcular_iluminacao(Vetor3d Pt,
                              	Vetor3d dr,
                              	Vetor3d P_F,
                             	Vetor3d I_F,
                              	Vetor3d I_A);

  		Vetor3d normal(Vetor3d Pt);
	};

#endif // ESFERA_H