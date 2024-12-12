#ifndef RAIO_H
#define RAIO_H

#include "./src/Objeto/Objeto.h"
#include <vector>
#include "funcoes_auxiliares.h"

using namespace funcoes_auxiliares;

class Raio {
public:
    Raio(const Vetor3d& origem, const Vetor3d& direcao);

    // Retorna o ponto no raio dado o parâmetro t
    Vetor3d noPonto(float t) const;

    // Calcula a interseção com uma lista de objetos e retorna o objeto mais próximo
    std::pair<float, const Objeto*> intersecaoMaisProxima(
        const std::vector<std::shared_ptr<Objeto>>& objetos) const;

private:
    Vetor3d origem;
    Vetor3d direcao;
};

#endif // RAIO_H
