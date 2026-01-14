#include "Renderer.h"
#include <glad/glad.h>

void Renderer::init()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    std::vector<float> vertices = {
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.9f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.9f,
        0.9f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.9f,
        0.9f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        1.0f,
        0.0f,
        0.9f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
    };

    mesh = new Mesh(vertices);
    mesh->transform.translate({-0.2f, -0.4f, 0.0f});
    mesh->transform.rotate(glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    mesh->transform.scale(glm::vec3(0.75f, 0.75f, 0));
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mesh->draw();
}