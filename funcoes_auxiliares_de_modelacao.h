// Created by Vitor de Albuquerque on 25/10/2024.

#ifndef FUNCOES_AUXILIARES_DE_MODELACAO_H
#define FUNCOES_AUXILIARES_DE_MODELACAO_H

#include "funcoes_auxiliares.h" // Incluindo o arquivo de operações vetoriais
using namespace funcoes_auxiliares;

namespace Auxiliares_de_modelacao {

struct Esfera; // Declaração antecipada de Esfera
struct Plano; // Declaração antecipada de Plano
struct Cilindro; // Declaração antecipada de Cilindro
struct Cone; // Declaração antecipada de Cone
struct Circulo; // Declaração antecipada de Circulo
struct Triangulo; // Declaração antecipada de Triangulo
struct Raio; // Declaração antecipada de Raio
struct Objeto; // Declaração antecipada de Objeto
struct MaterialSimples; // Declaração antecipada de MaterialSimples
struct FontePontual; // Declaração antecipada de FontePontual

struct Esfera
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

  Vetor3d normal(Vetor3d Pt);
};

struct Plano
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

struct Cilindro
{
  Vetor3d centro;
  float raio;
  float altura;
  Vetor3d direcao;

  Vetor3d K_d;
  Vetor3d K_e;
  Vetor3d K_a;
  float m;
//Definição Do Cilindro
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

  Vetor3d normal(Vetor3d Pt);
};
//Definição do Cone
struct Cone
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

  Vetor3d normal(Vetor3d Pt);
};
//Circulo de auxilio para tapar cone e cilindro
struct Circulo
{
    Vetor3d centro;
    float raio;
    Vetor3d normal;

    Vetor3d K_d;
    Vetor3d K_e;
    Vetor3d K_a;
    float m;

    Circulo(Vetor3d centro,
         float raio,
         Vetor3d normal,
         Vetor3d K_d,
         Vetor3d K_e,
         Vetor3d K_a,
         float m);

};
//triangulo para simular o cone 2d
struct Triangulo
{

    Vetor3d P0;
    Vetor3d P1;
    Vetor3d P2;

    Vetor3d normal;
    Vetor3d lado1;
    Vetor3d lado2;
    Vetor3d lado3;
    Vetor3d altura1;
    Vetor3d altura2;
    Vetor3d altura3;

    Vetor3d K_d;
    Vetor3d K_e;
    Vetor3d K_a;
    float m;

    Triangulo(Vetor3d P0,
         Vetor3d P1,
         Vetor3d P2,
         Vetor3d K_d,
         Vetor3d K_e,
         Vetor3d K_a,
         float m);

};

struct Raio
{
  Vetor3d P0;
  Vetor3d dr;

  Raio(Vetor3d P0, Vetor3d dr);
  Vetor3d no_ponto(float t);
  float intersecao(Objeto objeto);
  float intersecao(Esfera esfera);
  float intersecao(Plano plano); // Função de intersecção com Plano
  float intersecao(Cone cone);
  float intersecao(Cilindro cilindro);
  float intersecao(Circulo circulo);
  float intersecao(Triangulo triangulo);
};

struct FontePontual
{
   Vetor3d posicao;
   Vetor3d intensidade;

   FontePontual(Vetor3d posicao, Vetor3d intensidade);
};
//calculo do material para calcular iluminação
struct MaterialSimples
{
    Vetor3d K_d; 
    Vetor3d K_e;
    Vetor3d K_a;
    float m;

    MaterialSimples() {}

    MaterialSimples(Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m);
};

enum TipoObjeto
{
    OBJ_ESFERA, OBJ_PLANO, OBJ_CILINDRO, OBJ_CONE, OBJ_CIRCULO, OBJ_TRIANGULO
};

union UnionObjeto
{
    Esfera esfera;
    Plano plano;
    Cilindro cilindro;
    Cone cone;
    Circulo circulo;
    Triangulo triangulo;

    UnionObjeto();
};

struct Objeto
{
    TipoObjeto tipo;
    UnionObjeto obj;

    MaterialSimples material;

    Objeto(Esfera esfera);
    Objeto(Plano plano);
    Objeto(Cilindro cilindro);
    Objeto(Cone cone);
    Objeto(Circulo circulo);
    Objeto(Triangulo triangulo);

    Vetor3d normal(Vetor3d Pt);
};

namespace iluminacao {
    Vetor3d modelo_phong(Vetor3d Pt, Vetor3d dr, Vetor3d n, FontePontual fonte, Vetor3d I_A, MaterialSimples material);
    Vetor3d luz_ambiente(Vetor3d I_A, Vetor3d K_a);
}

// Funções max e min
double
max(double a, double b);
double
min(double a, double b);

}

#endif // FUNCOES_AUXILIARES_DE_MODELACAO_H
