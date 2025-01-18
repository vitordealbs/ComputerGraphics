#ifndef CALCULAR_INTERSECAO_H
#define CALCULAR_INTERSECAO_H

#include <vector>
#include "./Raio/Raio.h"
#include "./Objeto/Objeto.h"

std::pair<float, int> calcular_intersecao(Raio& raio, std::vector<Objeto>& objetos, int excluir = -1);

#endif