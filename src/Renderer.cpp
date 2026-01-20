#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void Renderer::init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    std::vector<float> vertices = {
        -0.5f, -0.5f,  0.5f,  1,0,0,  0,0,
        0.5f, -0.5f,  0.5f,  1,0,0,  1,0,
        0.5f,  0.5f,  0.5f,  1,0,0,  1,1,

        0.5f,  0.5f,  0.5f,  1,0,0,  1,1,
        -0.5f,  0.5f,  0.5f,  1,0,0,  0,1,
        -0.5f, -0.5f,  0.5f,  1,0,0,  0,0,

        0.5f, -0.5f, -0.5f,  0,1,0,  0,0,
        -0.5f, -0.5f, -0.5f,  0,1,0,  1,0,
        -0.5f,  0.5f, -0.5f,  0,1,0,  1,1,

        -0.5f,  0.5f, -0.5f,  0,1,0,  1,1,
        0.5f,  0.5f, -0.5f,  0,1,0,  0,1,
        0.5f, -0.5f, -0.5f,  0,1,0,  0,0,

        -0.5f, -0.5f, -0.5f,  0,0,1,  0,0,
        -0.5f, -0.5f,  0.5f,  0,0,1,  1,0,
        -0.5f,  0.5f,  0.5f,  0,0,1,  1,1,

        -0.5f,  0.5f,  0.5f,  0,0,1,  1,1,
        -0.5f,  0.5f, -0.5f,  0,0,1,  0,1,
        -0.5f, -0.5f, -0.5f,  0,0,1,  0,0,

        0.5f, -0.5f,  0.5f,  1,1,0,  0,0,
        0.5f, -0.5f, -0.5f,  1,1,0,  1,0,
        0.5f,  0.5f, -0.5f,  1,1,0,  1,1,

        0.5f,  0.5f, -0.5f,  1,1,0,  1,1,
        0.5f,  0.5f,  0.5f,  1,1,0,  0,1,
        0.5f, -0.5f,  0.5f,  1,1,0,  0,0,

        -0.5f,  0.5f,  0.5f,  0,1,1,  0,0,
        0.5f,  0.5f,  0.5f,  0,1,1,  1,0,
        0.5f,  0.5f, -0.5f,  0,1,1,  1,1,

        0.5f,  0.5f, -0.5f,  0,1,1,  1,1,
        -0.5f,  0.5f, -0.5f,  0,1,1,  0,1,
        -0.5f,  0.5f,  0.5f,  0,1,1,  0,0,

        -0.5f, -0.5f, -0.5f,  1,0,1,  0,0,
        0.5f, -0.5f, -0.5f,  1,0,1,  1,0,
        0.5f, -0.5f,  0.5f,  1,0,1,  1,1,

        0.5f, -0.5f,  0.5f,  1,0,1,  1,1,
        -0.5f, -0.5f,  0.5f,  1,0,1,  0,1,
        -0.5f, -0.5f, -0.5f,  1,0,1,  0,0,
    };

    mesh = new Mesh(vertices);
    mesh->transform.rotate(10.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::vec3 cameraPos = glm::vec3(10.0f, 0.0f, 10.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    camera = new Camera(cameraPos, cameraUp, cameraTarget);
}

void Renderer::render(bool isPaused, int windowWidth, int windowHeight)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mesh->getProgram());

    if(!isPaused)
    {
        spinY += 0.02f;
        if (spinY > glm::two_pi<float>())
            spinY -= glm::two_pi<float>();
    }

    float radius = 5.0f; 
    float camX = std::sin(spinY) * radius;
    float camZ = std::cos(spinY) * radius;
    
    glm::vec3 newCameraPos = glm::vec3(camX, 0.0f, camZ);

    camera->setPosition(newCameraPos);

    glm::mat4 view = camera->getLookAtMatrix();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), ((float) windowWidth / (float) windowHeight), 0.1f,
                                  100.0f);

    glUniformMatrix4fv(
        glGetUniformLocation(mesh->getProgram(), "view"),
        1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(
        glGetUniformLocation(mesh->getProgram(), "projection"),
        1, GL_FALSE, glm::value_ptr(projection));

    mesh->draw();
}