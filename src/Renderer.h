#pragma once
#include "Mesh.h"

class Renderer
{
public:
    void init();
    void render();

private:
    Mesh *mesh = nullptr;
};