#include "Renderer.h"
#include <glad/glad.h>

void Renderer::init()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    mesh = new Mesh();
    mesh->transform.translate({-0.4f, -0.4f, 0.0f});
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mesh->draw();
}