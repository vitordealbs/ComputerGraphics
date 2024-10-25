## Autores

- Vitor de Albuquerque - [@vitoralbq](https://www.github.com/vitoralbq)
- Luis Antônio Lopes - [@luis-dot-lopes](https://www.github.com/luis-dot-lopes)


# Computação Gráfica - Um breve projeto

No segundo semestre de 2024 é ofertado como cadeira obrigatória Computação Gráfica com o professor Dr. Creto Vidal. Nessa disciplina aprendemos a implementar conceitos de álgebra linear, métodos numéricos e design gráfico em algoritmos de computação gráfica.

O projeto inteiro foi feito em C++ com auxílio de uma biblioteca de design gráfico denominada [Raylib](https://www.raylib.com), a implementação dela é tranquila e serve tanto para visualizar quanto para implementar funções de álgebra linear. Entretanto, devido à requisitos propostos pelo professor, precisaríamos implementar as funções de álgebra linear à mão. Então apenas utilizamos raylib para pintar o background do projeto e as formas geométricas.

Vão ser ao todo 7 tarefas com a incrementação de novas ferramentas no próprio repositório, tudo que for sendo adicionado será explicado aqui!

## Aula 1 - introdução a CG

 Tivemos a explicação do professor de como a cadeira iria funcionar e introdução de alguns conceitos que, no começo, eram usuais do cotidiano humano: Canvas, pintura, janela, aramado, etc. A primeira implementação que tivemos que aprender foram de matrizes para projetarmos o frame para os desenhos que forem feitos no programa.
Além disso tivemos uma introdução aos eixos coordenados em 3 dimensões, pois na disciplina utilizaremos vetores para implementar os raios de iluminação e de distância. 

Tomamos orientação o olho do observador de lado, sendo o eixo X o que entra no olho, eixo Y o que está acima do olho e o eixo Z o que está a frente e atrás do olho.

Breve imagem de como funciona:


![Eixo Coordenados nos olhos](https://lh3.googleusercontent.com/pw/AP1GczNHu23zcwkk2Jkhdx_4BHyKi4BxKXt1nqfTmTv11qCAnOqxrNHKXh14lzl_2dnwtO8_T3gkYOAXTSCq2FrdAV90tP1rklFyvUkOlPtnt3-DqudSK0vnZr3ov83WsS3_cjoIDP9J8vm7hj_4QkHAMhAk=w799-h793-s-no-gm?authuser=0)


Além disso, construímos algumas equações que vão ser utilizadas no cenário e algumas percepções interessantes sobre CG.

O Centro da esfera, denominado cEsfera terá coordenadas (0,0,Ze) sendo Ze a distância do Centro da esfera para o olho do observador, Lcol e Llin são as dimensões da matriz que foi proposta. Além de H e w as dimensões reais do frame, em metros! Além disso temos dJanela que seria a distância do olho para a Janela.

Para início dos cálculos definiremos deltinha_x = $w/Lcol$ e deltinha_y = $h/Llin$. E definiremos o Ponto Superior Esquerdo como nosso ponto de partida, identificando com PSE = ($-w/2$,$h/2$, -d).

equações de raio e esfera:
$(x-x_centro)^2 + (y-y_centro)^2 + (z - z_centro)^2 = R^2$

$P(t) = Po + t * dr$

P(t), dr são vetores!

Da equação da Esfera temos: $a*ti^2$ + $b*ti$ + c = 0

sendo a = drx^2 + dry^2 + drz^2
b = drx(xo - x_centro) + dry(yo - y_centro) + drz(zo - z_centro) 
c = $(xo-x_centro)^2 + (yo-y_centro)^2 + (zo - z_centro)^2 + R^2$

## Rodando localmente
Requisitos: *Raylib* e *C++*

1) Clone o projeto

```bash
  git clone https://github.com/vitordealbs/ComputerGraphics
```

2) Entre no diretório do projeto

```bash
  cd ComputerGraphics
```
3) Faça a compilação do código, alterando a CMakeLists.txt para rodar os executáveis e a Raylib, extraindo os arquivos que vem nela

4) Pronto! Seu projeto está pronto para rodar!
