#ifndef OBJETO_COMPLEXO_H
#define OBJETO_COMPLEXO_H
#include "./funcoes_auxiliares.h"
#include "./src/Objeto/Objeto.h"
#include <vector>

struct ObjetoComplexo
{
  std::vector<Objeto> objetos;

  void transformar(Matriz mat);
  void adicionar_objeto(const Objeto& obj);
  void adicionar_objeto_complexo(const ObjetoComplexo& obj_complexo);
};

#endif // OBJETO_COMPLEXO_H
