#include "ObjetoComplexo.h"

void
ObjetoComplexo::transformar(Matriz mat)
{
  for (Objeto obj : objetos) {
    obj.transformar(mat);
  }
}

void
ObjetoComplexo::adicionar_objeto(Objeto obj)
{
  objetos.push_back(obj);
}
