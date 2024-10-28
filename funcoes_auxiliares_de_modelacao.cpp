// Created by Vitor de Albuquerque on 25/10/2024.

#include "funcoes_auxiliares_de_modelacao.h"
#include <cmath> // Para pow e sqrt
#include "funcoes_auxiliares.h" // Incluindo as operações vetoriais

using namespace funcoes_auxiliares; // Usando o namespace "Auxiliares"
using namespace Auxiliares_de_modelacao;

namespace Auxiliares_de_modelacao {

    double max(double a, double b) {
        return a + (b - a) * (a < b);
    }

    double min(double a, double b) {
        return a + (b - a) * (a > b);
    }

    // Definição do construtor da Esfera
    Esfera::Esfera(Vetor3d centro, float raio, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m)
        : centro(centro), raio(raio), K_d(K_d), K_e(K_e), K_a(K_a), m(m) {}

    Vetor3d Esfera::calcular_iluminacao(Vetor3d Pt, Vetor3d dr, Vetor3d P_F, Vetor3d I_F, Vetor3d I_A) {
        Vetor3d v = Auxiliares::Vetor3d_escala(dr, -1);
        Vetor3d l = Auxiliares::Vetor3dNormalizado(Auxiliares::Vetor3d_Subtrai(P_F, Pt));
        Vetor3d n = Auxiliares::Vetor3dNormalizado(Auxiliares::Vetor3d_Subtrai(Pt, centro));
        float dotproduct_nl = Auxiliares::Vetor3DotProduct(n, l);
        Vetor3d r = Auxiliares::Vetor3d_Subtrai(Auxiliares::Vetor3d_escala(n, 2 * dotproduct_nl), l);
        float dotproduct_vr = Auxiliares::Vetor3DotProduct(v, r);

        Vetor3d I_d = Auxiliares::Vetor3d_escala(Auxiliares::Vetor3d_Multiplica(K_d, I_F), max(dotproduct_nl, 0));
        Vetor3d I_e = Auxiliares::Vetor3d_escala(Auxiliares::Vetor3d_Multiplica(K_e, I_F), max(pow(dotproduct_vr, m), 0));
        Vetor3d I_a = Auxiliares::Vetor3d_Multiplica(K_a, I_A);

        Vetor3d I_total = Auxiliares::Vetor3d_Adiciona(I_d, Auxiliares::Vetor3d_Adiciona(I_e, I_a));
        return I_total;
    }

    // Definição do construtor de Raio
    Raio::Raio(Vetor3d P0, Vetor3d dr) : P0(P0), dr(dr) {}

    Vetor3d Raio::no_ponto(float t) {
        return Auxiliares::Vetor3d_Adiciona(P0, Auxiliares::Vetor3d_escala(dr, t));
    }

    float Raio::intersecao(Esfera esfera) {
        Vetor3d v = Auxiliares::Vetor3d_Subtrai(P0, esfera.centro);
        double a = Auxiliares::Vetor3DotProduct(dr, dr);
        double b = 2 * Auxiliares::Vetor3DotProduct(dr, v);
        double c = Auxiliares::Vetor3DotProduct(v, v) - esfera.raio * esfera.raio;
        double delta = b * b - 4 * a * c;
        if(delta < 0.0) {
            return -1.0f;
        }
        float t = (-b - sqrt(delta)) / (2 * a);
        if(t < 0.0) {
            t = (-b + sqrt(delta)) / (2 * a);
        }
        return t;
    }
    Plano::Plano(Vetor3d ponto, Vetor3d normal, Vetor3d K_d, Vetor3d K_e, Vetor3d K_a, float m)
        : ponto(ponto), normal(normal), K_d(K_d), K_e(K_e), K_a(K_a), m(m) {}
    float Raio::intersecao(Plano plano) {
        Vetor3d v = Auxiliares::Vetor3d_Subtrai(P0, plano.ponto);
        double a = Auxiliares::Vetor3DotProduct(dr, plano.normal);
        if(a == 0.0) {
            return -1.0;
        }
        double b = Auxiliares::Vetor3DotProduct(v, plano.normal);
        return -b / a;
    }
    Vetor3d Plano::calcular_iluminacao(Vetor3d Pt, Vetor3d dr, Vetor3d P_F, Vetor3d I_F, Vetor3d I_A) {
        Vetor3d v = Auxiliares::Vetor3d_escala(dr, -1);
        Vetor3d l = Auxiliares::Vetor3dNormalizado(Auxiliares::Vetor3d_Subtrai(P_F, Pt));
        float dotproduct_nl = Auxiliares::Vetor3DotProduct(normal, l);
        Vetor3d r = Auxiliares::Vetor3d_Subtrai(Auxiliares::Vetor3d_escala(normal, 2 * dotproduct_nl), l);
        float dotproduct_vr = Auxiliares::Vetor3DotProduct(v, r);

        Vetor3d I_d = Auxiliares::Vetor3d_escala(Auxiliares::Vetor3d_Multiplica(K_d, I_F), max(dotproduct_nl, 0));
        Vetor3d I_e = Auxiliares::Vetor3d_escala(Auxiliares::Vetor3d_Multiplica(K_e, I_F), max(pow(dotproduct_vr, m), 0));
        Vetor3d I_a = Auxiliares::Vetor3d_Multiplica(K_a, I_A);

        Vetor3d I_total = Auxiliares::Vetor3d_Adiciona(I_d, Auxiliares::Vetor3d_Adiciona(I_e, I_a));
        return I_total;
    }

}
