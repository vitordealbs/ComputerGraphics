#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include <raylib.h>
#include <src/ObjetoComplexo/ObjetoComplexo.h>

#include "./src/Camera/Camera3de.h"
#include "./src/Iluminacao/Iluminacao.h"
#include "./src/Objeto/Objeto.h"
using namespace iluminacao;
class RayTracer {
public:
    RayTracer(int width, int height, Camera3de* cam);
    void inicializarCena();
    void renderizar();
    void atualizarCamera(Camera3de* cam);
    RenderTexture2D tela;
    int W_C, H_C;
    float W_J, H_J, d;
    int nLin, nCol;
    Camera3de* camera;
    std::vector<Objeto> objects_flat;
    std::vector<ObjetoComplexo> complexObjects;
    Vetor3d I_A;
    Vetor3d P_F, I_F;
    FonteDirecional minhaDirecional;
    FonteSpot minhaSpot;
    

};

#endif