#pragma once
#include "Mesh.h"

class Renderer
{
public:
    void init();
    void render(bool isPaused, int windowWidth, int windowHeight);

    // just for a temporary hover+rotation animation
    float hoverY = 0.0f;
    float hoverDir = 1.0f;
    float spinY = 0.0f;

private:
    Mesh *mesh = nullptr;
};