#ifndef MATERIAL_H
#define MATERIAL_H

#include "funcoes_auxiliares.h"
using namespace funcoes_auxiliares;
class Material {
public:
    Material(); // Construtor padrão
    Material(const Vetor3d& K_d,
             const Vetor3d& K_e,
             const Vetor3d& K_a,
             float m); // Construtor parametrizado


    Vetor3d getKd() const;
    Vetor3d getKe() const;
    Vetor3d getKa() const;
    float getM() const;

    // Setters
    void setKd(const Vetor3d& K_d);
    void setKe(const Vetor3d& K_e);
    void setKa(const Vetor3d& K_a);
    void setM(float m);

private:
    Vetor3d K_d;
    Vetor3d K_e;
    Vetor3d K_a;
    float m;
};

#endif // MATERIAL_H