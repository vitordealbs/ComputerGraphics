// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_DE_MODELACAO_H
#define FUNCOES_AUXILIARES_DE_MODELACAO_H

#include "funcoes_auxiliares.h" // Incluindo o arquivo de operações vetoriais
using namespace funcoes_auxiliares;

namespace Auxiliares_de_modelacao {

struct Objeto
{
  virtual Vetor3d calcular_iluminacao(Vetor3d Pt,
                                      Vetor3d dr,
                                      Vetor3d P_F,
                                      Vetor3d I_F,
                                      Vetor3d I_A) = 0;
};

struct Plano; // Declaração antecipada de Plano

struct Esfera : Objeto
{
  Vetor3d centro;
  float raio;
  Vetor3d K_d;
  Vetor3d K_e;
  Vetor3d K_a;
  float m;

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
};

struct Plano : Objeto
{
  Vetor3d ponto;
  Vetor3d normal;
  Vetor3d K_d;
  Vetor3d K_e;
  Vetor3d K_a;
  float m;

  // Construtor correto para inicializar as propriedades do plano
  Plano(Vetor3d ponto,
        Vetor3d normal,
        Vetor3d K_d,
        Vetor3d K_e,
        Vetor3d K_a,
        float m);

  static Plano tres_pontos(Vetor3d P1,
                           Vetor3d P2,
                           Vetor3d P3,
                           Vetor3d K_d,
                           Vetor3d K_e,
                           Vetor3d K_a,
                           float m);

  Vetor3d calcular_iluminacao(Vetor3d Pt,
                              Vetor3d dr,
                              Vetor3d P_F,
                              Vetor3d I_F,
                              Vetor3d I_A);
};

struct Cilindro : Objeto
{
  Vetor3d centro;
  float raio;
  float altura;
  Vetor3d direcao;

  Vetor3d K_d;
  Vetor3d K_e;
  Vetor3d K_a;
  float m;

  Cilindro(Vetor3d centro,
           float raio,
           float altura,
           Vetor3d direcao,
           Vetor3d K_d,
           Vetor3d K_e,
           Vetor3d K_a,
           float m);

  Vetor3d calcular_iluminacao(Vetor3d Pt,
                              Vetor3d dr,
                              Vetor3d P_F,
                              Vetor3d I_F,
                              Vetor3d I_A);
};

struct Cone : Objeto
{
  Vetor3d centro;
  float raio;
  float altura;
  Vetor3d direcao;

  Vetor3d K_d;
  Vetor3d K_e;
  Vetor3d K_a;
  float m;

  Cone(Vetor3d centro,
       float raio,
       float altura,
       Vetor3d direcao,
       Vetor3d K_d,
       Vetor3d K_e,
       Vetor3d K_a,
       float m);

  Vetor3d calcular_iluminacao(Vetor3d Pt,
                              Vetor3d dr,
                              Vetor3d P_F,
                              Vetor3d I_F,
                              Vetor3d I_A);
};

struct Raio
{
  Vetor3d P0;
  Vetor3d dr;

  Raio(Vetor3d P0, Vetor3d dr);
  Vetor3d no_ponto(float t);
  float intersecao(Esfera esfera);
  float intersecao(Plano plano); // Função de intersecção com Plano
  float intersecao(Cone cone);
  float intersecao(Cilindro cilindro);
};

// Funções max e min
double
max(double a, double b);
double
min(double a, double b);

}

#endif // FUNCOES_AUXILIARES_DE_MODELACAO_H
