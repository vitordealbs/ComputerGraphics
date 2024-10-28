## Autores

- Vitor de Albuquerque - [@vitoralbq](https://www.github.com/vitoralbq)
- Luis Antônio Lopes - [@luis-dot-lopes](https://www.github.com/luis-dot-lopes)
  
Trello do Projeto: https://trello.com/invite/b/671e3fdc7f2efb43632badae/ATTI92b2fb094770c151fbbd527004b91e271CF34B5F/computacao-grafica

# Computação Gráfica - Um breve projeto

No segundo semestre de 2024 é ofertado como cadeira obrigatória Computação Gráfica com o professor Dr. Creto Vidal. Nessa disciplina aprendemos a implementar conceitos de álgebra linear, métodos numéricos e design gráfico em algoritmos de computação gráfica.

O projeto inteiro foi feito em C++ com auxílio de uma biblioteca de design gráfico denominada [Raylib](https://www.raylib.com), a implementação dela é tranquila e serve tanto para visualizar quanto para implementar funções de álgebra linear. Entretanto, devido à requisitos propostos pelo professor, precisaríamos implementar as funções de álgebra linear à mão. Então apenas utilizamos raylib para pintar o background do projeto e as formas geométricas.

Vão ser ao todo 7 tarefas com a incrementação de novas ferramentas no próprio repositório, tudo que for sendo adicionado será explicado aqui!

## Aula 1 - introdução a CG

 Tivemos a explicação do professor de como a cadeira iria funcionar e introdução de alguns conceitos que, no começo, eram usuais do cotidiano humano: Canvas, pintura, janela, aramado, etc. A primeira implementação que tivemos que aprender foram de matrizes para projetarmos o frame para os desenhos que forem feitos no programa.
Além disso tivemos uma introdução aos eixos coordenados em 3 dimensões, pois na disciplina utilizaremos vetores para implementar os raios de iluminação e de distância. 

Tomamos orientação o olho do observador de lado, sendo o eixo X o que entra no olho, eixo Y o que está acima do olho e o eixo Z o que está a frente e atrás do olho.

Breve imagem de como funciona:


<img src = "https://lh3.googleusercontent.com/pw/AP1GczNHu23zcwkk2Jkhdx_4BHyKi4BxKXt1nqfTmTv11qCAnOqxrNHKXh14lzl_2dnwtO8_T3gkYOAXTSCq2FrdAV90tP1rklFyvUkOlPtnt3-DqudSK0vnZr3ov83WsS3_cjoIDP9J8vm7hj_4QkHAMhAk=w799-h793-s-no-gm?authuser=0" height = "250px">

Além disso, construímos algumas equações que vão ser utilizadas no cenário e algumas percepções interessantes sobre CG.

O Centro da esfera, denominado cEsfera terá coordenadas (0,0,Ze) sendo Ze a distância do Centro da esfera para o olho do observador, Lcol e Llin são as dimensões da matriz que foi proposta. Além de H e w as dimensões reais do frame, em metros! Além disso temos dJanela que seria a distância do olho para a Janela.

Para início dos cálculos definiremos $\delta$ _x = $\frac{W}{Lcol}$  e $\delta$ _y = $\frac{H}{Llin}$. E definiremos o Ponto Superior Esquerdo como nosso ponto de partida, identificando com PSE = ($\frac{W}{2}$ , $\frac{H}{2}$ , -d).

equações de raio e esfera:
$(x-x_c)^2 + (y - y_c)^2 + (z - z_c)^2 = R^2$

$\vec{P(t)} = Po + t * \vec{dr}$ 


Da equação da Esfera temos: $a* t_i^2  + b*t_i + c = 0$

coeficientes:

$a = \vec{dr}_x^2 + \vec{dr}_y^2 + \vec{dr}_z^2$

$b = \vec{dr}_x(x_o - x_c) + \vec{dr}_y(y_o - y_c) + \vec{dr}_z(z_o - z_c)$

$c = (x_o-x_c)^2 + (y_o-y_c)^2 + (z_o - z_c)^2 + R^2$

## Preparação para as Tarefas (Funções Auxiliares)
Como dito anteriormente, Creto não deixou utilizar funções pré-prontas, por isso tivemos que implementar algumas funções vetoriais do zero e criar um Struct para vetores em 3 dimensões, denominado Vetor3d: 

Vetor3d_escala(Vetor3d v, float scalar): Recebe um vetor e um número escalar para fazer uma multiplicação escalar com o vetor, aplicando a fórmula $\ \vec{v}_1x * scalar ; \vec{v}_1y * scalar ; \vec{v}_1z * scalar $

Vetor3DotProduct(Vetor3d v1, Vetor3d v2): ecebe dois vetores e faz o produto de pontos entre eles, aplicando a fórmula de subtração de vetores $\ \vec{v}_1x * \vec{v}_2x + \vec{v}_1y * \vec{v}_2y + \vec{v}_1z * \vec{v}_2z $

Vetor3_tamanho(Vetor3d v): Recebe um vetor e calcula o tamanho dele, aplicando a fórmula $`\sqrt{\vec{v}_x * \vec{v}_x + \vec{v}_y * \vec{v}_y + \vec{v}_z * \vec{v}_z}`$

Vetor3dNormalizado(Vetor3d v): Recebe um vetor e normaliza o tamanho dele para ser 1, mantendo a direção original, comparando se ele é menor ou igual a 1

Vetor3d_Subtrai(Vetor3d v1, Vetor3d v2): Recebe dois vetores e faz a subtração vetorial entre eles, aplicando a fórmula $\ \vec{v}_1x - \vec{v}_2x, \vec{v}_1y - \vec{v}_2y, \vec{v}_1z - \vec{v}_2z $

Vetor3d_Adiciona(Vetor3d v1, Vetor3d v2): Recebe dois vetores e faz a adição vetorial entre eles, aplicando a fórmula $\ \vec{v}_1x + \vec{v}_2x, \vec{v}_1y + \vec{v}_2y, \vec{v}_1z + \vec{v}_2z $

Vetor3d_Multiplica(Vetor3d v1, Vetor3d v2): Recebe dois vetores e faz a multiplicação vetorial entre eles, aplicando a fórmula $\ \vec{v}_1x * \vec{v}_2x, \vec{v}_1y * \vec{v}_2y, \vec{v}_1z * \vec{v}_2z $

## Tarefa 1 
Requisitos: Pintar uma esfera no Canvas, definir o tamanho do painel, raio da esfera deve ser armazenado em rEsfera, cor do background cinza (100,100,100) , esfera deve ser RGB (255,0,0)
Como já definimos os pontos, precisamos nos preocupar apenas com o loop do projeto para pintar os pixels
cada pixel possui coordenadas P($x_p, y_p, z_p$), z_p é constante e sempre será $z_p$ = -dJanela, $y_p$ = $PSE_y$ - $\frac{Delta_y}{2}\$ - i * $\delta$ y , $x_p$ = $x_p$ = $PSE_x$ + $\delta$ x * 0.5 + j * $\delta$ x;

SENDO PSE = { $\frac{-wJanela}{2}$, $\frac{hJanela}{2}$, -dJanela };

Verificamos se as retas de luz interceptam a esfera e verificamos o delta, visto que precisamos igualar uma equação de segundo grau com a de primeiro grau.

Se o $\Delta >= 0$ temos interceptações e pintamos da cor que o professor pediu, vermelha

Se não a gente pinta da cor do Background.

Dessa forma obtemos:


<img src = "https://lh3.googleusercontent.com/pw/AP1GczNvS1MePpnp4cwV74iyfh5o90bNHSefxCZbVmqI9pmsKPvuy0DroYwdVXBM8yl3t9gYpEcFzCPE1BB2d9ncI9vLlk5ZfE6C7Ypt1LnMIcBuMsjNwh5oskMtVCgqeXtym2ZT0eiODNmPMYj2eVM0F5ET=w799-h603-s-no-gm?authuser=0" height = "250px">

Para saber mais do código acesse nossa documentação https://docs.google.com/document/d/1fLCBMWdit_Z32bfVOdO8JX0UjuQu0ShCus9_v9Hmhl4/edit?usp=sharing

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
