#ifndef OBJETO_H
#define OBJETO_H

#include "./src/Material/Material.h"
#include "funcoes_auxiliares.h"
#include <memory>

class Objeto {
public:
 Objeto(); // Construtor padrão
 virtual ~Objeto() = default; // Destrutor virtual

 // Métodos para interseção e iluminação
 virtual float intersecao(const Vetor3d& origem,
                          const Vetor3d& direcao) const = 0;
 virtual Vetor3d calcularIluminacao(
     const Vetor3d& Pt,
     const Vetor3d& dr,
     const Vetor3d& P_F,
     const Vetor3d& I_F,
     const Vetor3d& I_A) const = 0;

 // Métodos para gerenciamento do material
 void setMaterial(const Material& material);
 Material getMaterial() const;

protected:
 Material material; // Material associado ao objeto
};

#endif // OBJETO_H
