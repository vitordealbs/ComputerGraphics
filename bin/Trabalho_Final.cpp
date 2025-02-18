#include <cstdio>
#include <raylib.h>
#include "./src/Camera/Camera3de.h"
#include "./src/rayTracer/RayTracer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trabalho Final");
    SetTargetFPS(60);

    Vetor3d Eye = {140.0f, 125.0f, 800.0f};
    Vetor3d At = {140.0f, 125.0f, 500.0f};
    Vetor3d Up = {140.0f, 325.0f, 500.0f};
    Camera3de camera(Eye, At, Up);

    RayTracer rayTracer(SCREEN_WIDTH, SCREEN_HEIGHT, &camera);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        rayTracer.renderizar();
        DrawTextureRec(rayTracer.tela.texture, {0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT}, {0, 0}, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}