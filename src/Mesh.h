#pragma once
#include "Transform.h"
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(std::vector<float> &vertices);
    void draw();
    Transform transform;

    GLuint getProgram() const { return program; }

private:
    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint program = 0;
    GLuint texture = 0;
    GLuint vertexCount_;
    std::vector<float> vertices_;
};