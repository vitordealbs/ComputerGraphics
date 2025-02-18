#include "RayTracer.h"

#include <cmath>

#include "funcoes_auxiliares.h"
#include "src/inicializar_objetos.h"
#include "src/calcular_intersecao.h"
#include <iostream>

#include "src/objetosTrabalhofinal.h"

RayTracer::RayTracer(int width, int height, Camera3de* cam)
    : W_C(width), H_C(height), camera(cam), W_J(60.0f), H_J(60.0f), d(50.0f),
      nLin(500), nCol(500), I_A({0.2f, 0.2f, 0.2f}),
      P_F({300.0f, 300.0f, 1500.0f}), I_F({0.5f, 0.5f, 0.5f}),
      minhaDirecional({-1.0f, -0.3f, -0.2f}, {0.2f, 0.2f, 0.2f}),
      minhaSpot({200.0f, 400.0f, 600.0f}, {0.0f, -1.0f, -1.0f}, 0.5f, {0.2f, 0.2f, 0.2f}) {

    tela = LoadRenderTexture(W_C, H_C);
    inicializarCena();
}

void RayTracer::inicializarCena() {
    std::cout << "Inicializando cena..." << std::endl;
    inicializar_objetosfinal(objects_flat, complexObjects);

    for (ObjetoComplexo& objeto_complexo : complexObjects) {
        flatten_objetos(objeto_complexo, objects_flat);
    }

    Matriz M_wc = camera->getTransformationMatrix();
    for (auto& objeto : objects_flat) {
        objeto.transformar(M_wc);
    }
}

void RayTracer::renderizar() {
    std::cout << "Renderizando cena..." << std::endl;

    double deltinhax = W_J / nCol, deltinhay = H_J / nLin;
    Vetor3d Ponto_Superior_Esquerdo = {-W_J * 0.5f, W_J * 0.5f, -d};
    std::vector<Color> pixel_buffer(nLin * nCol, WHITE);

    Matriz M_wc = camera->getTransformationMatrix();
    P_F = (M_wc * P_F.ponto4d()).vetor3d();

    BeginTextureMode(tela);
    ClearBackground(BLACK);

    #pragma omp parallel for
    for (int i = 0; i < nLin; ++i) {
        for (int j = 0; j < nCol; ++j) {
            float yp = Ponto_Superior_Esquerdo.y - deltinhay * 0.5f - i * deltinhay;
            float xp = Ponto_Superior_Esquerdo.x + deltinhax * j + 0.5f * deltinhax;
            Vetor3d P = {xp, yp, -d};
            Vetor3d dr = P.normalizado();
            Raio raio(camera->position, dr);

            auto [t, object] = calcular_intersecao(raio, objects_flat);
            Vetor3d I_total = I_A;

            if (t > 0.0f) {
                Vetor3d Pt = raio.no_ponto(t);
                Vetor3d normal = objects_flat[object].normal(Pt);
                MaterialSimples material = objects_flat[object].material;

                Vetor3d dr_luz = (P_F - Pt).normalizado();
                Raio light_ray(Pt, dr_luz);
                float distPF = (P_F - Pt).tamanho();
                auto [t_luz, _] = calcular_intersecao(light_ray, objects_flat, object);

                if (t_luz < 0.0f || t_luz > distPF) {
                    Vetor3d corPontual = luz_ambiente(I_A, material.K_a);
                    I_total = I_total + corPontual;
                }

                Vetor3d corDir = modelo_phong(Pt, raio.dr, normal, minhaDirecional, material);
                I_total = I_total + corDir;

                float r = fmin(I_total.x * 255.0f, 255.0f);
                float g = fmin(I_total.y * 255.0f, 255.0f);
                float b = fmin(I_total.z * 255.0f, 255.0f);

                pixel_buffer[i * nCol + j] = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
            }
        }
    }

    for (int i = 0; i < nLin; ++i) {
        for (int j = 0; j < nCol; ++j) {
            DrawPixel(j, i, pixel_buffer[i * nCol + j]);
        }
    }

    EndTextureMode();
    std::cout << "Renderização completa!" << std::endl;
}

void RayTracer::atualizarCamera(Camera3de* cam) {
    this->camera = cam;
    inicializarCena();
}
