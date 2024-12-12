#include "Material.h"

// Construtor padrão
Material::Material()
    : K_d({ 0.0f, 0.0f, 0.0f }),
      K_e({ 0.0f, 0.0f, 0.0f }),
      K_a({ 0.0f, 0.0f, 0.0f }),
      m(0.0f) {}

// Construtor parametrizado
Material::Material(const Vetor3d& K_d,
                   const Vetor3d& K_e,
                   const Vetor3d& K_a,
                   float m)
    : K_d(K_d), K_e(K_e), K_a(K_a), m(m) {}

// Getters
Vetor3d Material::getKd() const {
    return K_d;
}

Vetor3d Material::getKe() const {
    return K_e;
}

Vetor3d Material::getKa() const {
    return K_a;
}

float Material::getM() const {
    return m;
}

// Setters
void Material::setKd(const Vetor3d& K_d) {
    this->K_d = K_d;
}

void Material::setKe(const Vetor3d& K_e) {
    this->K_e = K_e;
}

void Material::setKa(const Vetor3d& K_a) {
    this->K_a = K_a;
}

void Material::setM(float m) {
    this->m = m;
}