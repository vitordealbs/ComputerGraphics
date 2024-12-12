#include "Objeto.h"

// Construtor padrão
Objeto::Objeto()
    : material(Material()) {}

// Definir material
void Objeto::setMaterial(const Material& material) {
    this->material = material;
}

// Obter material
Material Objeto::getMaterial() const {
    return material;
}

