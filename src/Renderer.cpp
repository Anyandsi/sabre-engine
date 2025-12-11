#include "Renderer.h"
#include <glad/glad.h>

void Renderer::init()
{
    glClearColor(0.2f, 0.27f, 0.3f, 1.0f);
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
}