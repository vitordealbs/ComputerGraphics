//
// Created by I590177 on 12/12/2024.
//

#include "Raio.h"
#include "Raio.h"

using namespace funcoes_auxiliares;

Raio::Raio(const Vetor3d& origem, const Vetor3d& direcao)
    : origem(origem), direcao(Vetor3d(direcao).normalizado()) {}

Vetor3d Raio::noPonto(float t) const {
    return origem + direcao * t;
}

std::pair<float, const Objeto*> Raio::intersecaoMaisProxima(
    const std::vector<std::shared_ptr<Objeto>>& objetos) const {
    const Objeto* objetoMaisProximo = nullptr;
    float menorT = -1.0f;

    for (const auto& objeto : objetos) {
        float t = objeto->intersecao(origem, direcao);
        if (t > 0.0f && (menorT < 0.0f || t < menorT)) {
            menorT = t;
            objetoMaisProximo = objeto.get();
        }
    }

    return {menorT, objetoMaisProximo};
}
