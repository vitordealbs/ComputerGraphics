//
// Created by Vitor on 01/02/2025.
//

#include "objetosTrabalhofinal.h"
#include <iostream>
#include <raylib.h>

#include "inicializar_objetos.h"
#include "./PlanoTextura/PlanoTextura.h"
#include "./Malha/Malha.h"

void inicializar_objetosfinal(std::vector<Objeto>& objects_flat, std::vector<ObjetoComplexo>& complexObjects) {
    Image textura_grama = LoadImage("../assets/grama.png");
    Color* pixels_textura_grama = LoadImageColors(textura_grama);
    if (!textura_grama.data) {
        std::cerr << "Erro ao carregar textura de grama.\n";
        return;
    }
    Textura texturaG(pixels_textura_grama,
                     textura_grama.width,
                     textura_grama.height,
                     textura_grama.width,
                     textura_grama.height,
                     10.0f);

    PlanoTextura plano_grama(
        { 0.0f, -10.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f },
        texturaG);
    objects_flat.push_back(plano_grama);
    std::cout << "Inicializou plano da grama.\n";

    Image textura_ceu = LoadImage("../assets/img.png");
    Color* pixels_textura_ceu = LoadImageColors(textura_ceu);
    if (!textura_ceu.data) {
        std::cerr << "Erro ao carregar textura do céu.\n";
        return;
    }
    Textura texturaC(pixels_textura_ceu,
                     textura_ceu.width,
                     textura_ceu.height,
                     textura_ceu.width/0.01f,
                     textura_ceu.height/0.01f,
                     1.0f);

    PlanoTextura plano_ceu({ 1000.0f, 250.0f, -20000.0f },
                           { 1.0f, 0.0f, 0.0f },
                           { 0.0f, 1.0f, 0.0f },
                           texturaC);
    objects_flat.push_back(plano_ceu);
    std::cout << "Inicializou plano do céu.\n";

    // 2) QUADRA ELEVADA
    Malha quadra;
    quadra.inicializar_cubo({0,0,0}, 1.0f, {0.7f,0.7f,0.7f},{0.7f,0.7f,0.7f},{0.7f,0.7f,0.7f}, 32);
    quadra.transformar(
        Matriz::translacao({150.0f, 0.0f, 300.0f})
        * Matriz::escala({400.0f, 0.00000000000001f, 1000.0f})
    );
    ObjetoComplexo quadraElevada;
    quadraElevada.adicionar_objeto(quadra);
    complexObjects.push_back(quadraElevada);

    // 3) ARQUIBANCADA (3 degraus)
    ObjetoComplexo arquibancada;
    Malha degrau1, degrau2, degrau3;
    Vetor3d corArquib = {0.5f, 0.5f, 0.5f};
    Vetor3d corArquib2 = {0.7f, 0.7f, 0.7f};
    Vetor3d corArquib3 = {0.9f, 0.9f, 0.9f};
    float m_arquib = 16.0f;

    degrau1.inicializar_cubo({0,0,0}, 1.0f, corArquib, corArquib, corArquib, m_arquib);
    degrau2.inicializar_cubo({0,0,0}, 1.0f, corArquib2, corArquib2, corArquib2, m_arquib);
    degrau3.inicializar_cubo({0,0,0}, 1.0f, corArquib3, corArquib3, corArquib3, m_arquib);

    degrau1.transformar(
        Matriz::translacao({500.0f, 0.0f, 250.0f}) *
        Matriz::escala({50.0f, 75.0f, 1000.0f})
    );
    degrau2.transformar(
    Matriz::translacao({550.0f, 0.0f, 250.0f}) *
    Matriz::escala({50.0f, 150.0f, 1000.0f})
    );
    degrau3.transformar(
    Matriz::translacao({600.0f, 0.0f, 250.0f}) *
    Matriz::escala({50.0f, 200.0f, 1000.0f})
    );

    arquibancada.adicionar_objeto(degrau1);
    arquibancada.adicionar_objeto(degrau2);
    arquibancada.adicionar_objeto(degrau3);
    complexObjects.push_back(arquibancada);

    // 4) BOLA NO CENTRO (raio maior, se quiser)
    Esfera bola(
        {150.0f, 10.0f, 300.0f},
        10.0f,
        {1.0f,0.2f,0.2f},
        {1.0f,1.0f,1.0f},
        {0.1f,0.1f,0.1f},
        32.0f
    );
    objects_flat.push_back(bola);

    // 5) DUAS ÁRVORES
    auto criarArvore = [&](float x, float z) {
        ObjetoComplexo arvore;
        // Tronco
        Cilindro tronco(
            {x, 0.0f, z},
            5.0f,
            150.0f,
            {0.0f, 1.0f, 0.0f},
            {0.5f,0.25f,0.1f},
            {0.5f,0.25f,0.1f},
            {0.1f,0.1f,0.1f},
            8.0f
        );

        // Copa (agora um cone)
        Cone copa(
            {x, 150.0f, z},
            80.0f,
            150.0f,
            {0.0f, 1.0f, 0.0f},
            {0.0f,0.5f,0.0f},
            {0.0f,0.5f,0.0f},
            {0.1f,0.1f,0.1f},
            8.0f
        );

        arvore.adicionar_objeto(tronco);
        arvore.adicionar_objeto(copa);

        return arvore;
    };

    ObjetoComplexo arv1 = criarArvore(500.0f, -400.0f);
    ObjetoComplexo arv2 = criarArvore(500.0f, 850.0f);

    complexObjects.push_back(arv1);
    complexObjects.push_back(arv2);

    // 6) DUAS TRAVES
    auto criarTrave = [&](float zPos) {
        float xLeft  = 50.0f;
        float xRight = 200.0f;
        float altura = 150.0f;

        ObjetoComplexo trave;

        // Poste esquerdo
        Cilindro posteE(
            {xLeft, 0.0f, zPos},
            5.0f,
            altura,
            {0.0f, 1.0f, 0.0f},
            {1.0f,1.0f,1.0f},
            {1.0f,1.0f,1.0f},
            {0.2f,0.2f,0.2f},
            16.0f
        );

        // Poste direito
        Cilindro posteD(
            {xRight, 0.0f, zPos},
            5.0f,
            altura,
            {0.0f, 1.0f, 0.0f},
            {1.0f,1.0f,1.0f},
            {1.0f,1.0f,1.0f},
            {0.2f,0.2f,0.2f},
            16.0f
        );

        float xCenter = (xLeft + xRight) * 0.2f;
        float travessaComprimento = 150.0f;
        Cilindro barra(
            { xCenter, altura, zPos },
            5.0f,
            travessaComprimento,
            {1.0f, 0.0f, 0.0f},
            {1.0f,1.0f,1.0f},
            {1.0f,1.0f,1.0f},
            {0.2f,0.2f,0.2f},
            16.0f
        );

        trave.adicionar_objeto(posteE);
        trave.adicionar_objeto(posteD);
        trave.adicionar_objeto(barra);

        return trave;
    };
    ObjetoComplexo trave1 = criarTrave(-100.0f);
    ObjetoComplexo trave2 = criarTrave(800.0f);

    complexObjects.push_back(trave1);
    complexObjects.push_back(trave2);


    // 7) CESTA DE BASQUETE
auto criarCestaBasquete = [&](float x, float z) {
    ObjetoComplexo cesta;


    Cilindro asteVertical(
        {x, 0.0f, z},
        2.0f,
        200.0f,
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {0.2f, 0.2f, 0.2f},
        16.0f
    );

    Cilindro asteHorizontal(
        {x, 200.0f, z - 20.0f},
        2.0f,
        50.0f,
        {0.0f, 0.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {0.2f, 0.2f, 0.2f},
        16.0f
    );


    cesta.adicionar_objeto(asteVertical);
    cesta.adicionar_objeto(asteHorizontal);
    Cilindro aro1(
            {125, 200.0f,  -25.0f},
            30.0f,
            10.0f,
            {0.0f, 1.0f, 0.0f},
            {1.0f, 0.5f, 0.0f},
            {1.0f, 0.5f, 0.0f},
            {0.2f, 0.1f, 0.0f},
            16.0f
        );
    Cilindro aro2(
            {125, 200.0f,  800.0f},
            30.0f,
            10.0f,
            {0.0f, 1.0f, 0.0f},
            {1.0f, 0.5f, 0.0f},
            {1.0f, 0.5f, 0.0f},
            {0.2f, 0.1f, 0.0f},
            16.0f
        );
    cesta.adicionar_objeto(aro1);
    cesta.adicionar_objeto(aro2);

    Malha malha_back1, malha_back2;
    malha_back1.inicializar_cubo({0,0,0}, 1.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 16.0f);
    malha_back2.inicializar_cubo({0,0,0}, 1.0f, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 16.0f);
    malha_back1.transformar(Matriz::translacao({125.0f, 230.0f, 830.0f}) *
    Matriz::escala({100.0f, 100.0f, 10.0f}));
    malha_back2.transformar(Matriz::translacao({125.0f, 230.0f, -75.0f}) *
    Matriz::escala({100.0f, 100.0f, 10.0f}));
    cesta.adicionar_objeto(malha_back1);
    cesta.adicionar_objeto(malha_back2);

    return cesta;
};


    ObjetoComplexo cesta1 = criarCestaBasquete(125.0f, -80.0f);
    ObjetoComplexo cesta2 = criarCestaBasquete(125.0f,  820.0f);



    complexObjects.push_back(cesta1);
    complexObjects.push_back(cesta2);
}
