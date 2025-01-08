#include "malha.h"

Malha::Malha() {}

void
Malha::inicializar_cubo(const Vetor3d& centro,
                        float tamanho,
                        const Vetor3d& K_d,
                        const Vetor3d& K_e,
                        const Vetor3d& K_a,
                        float m)
{
  material = MaterialSimples(K_d, K_e, K_a, m);
  float h = tamanho / 2.0f;

  // Criar vértices do cubo
  vertices = { { centro.x - h, centro.y - h, centro.z - h },
               { centro.x + h, centro.y - h, centro.z - h },
               { centro.x + h, centro.y + h, centro.z - h },
               { centro.x - h, centro.y + h, centro.z - h },
               { centro.x - h, centro.y - h, centro.z + h },
               { centro.x + h, centro.y - h, centro.z + h },
               { centro.x + h, centro.y + h, centro.z + h },
               { centro.x - h, centro.y + h, centro.z + h } };

  // Criar faces do cubo (6 faces, 2 triângulos por face)
  faces = {
    Triangulo(vertices[0], vertices[1], vertices[2], K_d, K_e, K_a, m),
    Triangulo(
      vertices[0], vertices[2], vertices[3], K_d, K_e, K_a, m), // Frente
    Triangulo(vertices[4], vertices[5], vertices[6], K_d, K_e, K_a, m),
    Triangulo(vertices[4], vertices[6], vertices[7], K_d, K_e, K_a, m), // Trás
    Triangulo(vertices[0], vertices[1], vertices[5], K_d, K_e, K_a, m),
    Triangulo(vertices[0], vertices[5], vertices[4], K_d, K_e, K_a, m), // Baixo
    Triangulo(vertices[2], vertices[3], vertices[7], K_d, K_e, K_a, m),
    Triangulo(vertices[2], vertices[7], vertices[6], K_d, K_e, K_a, m), // Cima
    Triangulo(vertices[0], vertices[3], vertices[7], K_d, K_e, K_a, m),
    Triangulo(
      vertices[0], vertices[7], vertices[4], K_d, K_e, K_a, m), // Esquerda
    Triangulo(vertices[1], vertices[2], vertices[6], K_d, K_e, K_a, m),
    Triangulo(
      vertices[1], vertices[6], vertices[5], K_d, K_e, K_a, m) // Direita
  };
}

void
Malha::transformar(Matriz mat)
{
  
}
