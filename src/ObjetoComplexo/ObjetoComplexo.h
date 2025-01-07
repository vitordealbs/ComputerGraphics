#ifndef OBJETO_COMPLEXO_H
#define OBJETO_COMPLEXO_H
#include "../Objeto/Objeto.h"
#include <vector>

struct ObjetoComplexo
{
  std::vector<Objeto> objetos;

  void transformar(Matriz mat);
  void adicionar_objeto(Objeto obj);
};

#endif // OBJETO_COMPLEXO_H
