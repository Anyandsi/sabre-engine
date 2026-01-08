#pragma once
#include "Transform.h"
#include <glad/glad.h>

class Mesh
{
public:
    Mesh();
    void draw();
    Transform transform;

private:
    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint program = 0;
    GLuint texture = 0;
};