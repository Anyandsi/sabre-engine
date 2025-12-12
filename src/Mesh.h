#pragma once
#include <glad/glad.h>

class Mesh
{
public:
    Mesh();
    void draw();

private:
    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint program = 0;
};