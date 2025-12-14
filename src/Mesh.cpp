#include "Mesh.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

static void checkShaderCompilation(GLuint s, const char *label)
{
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (ok)
        return;

    char log[1024];
    glGetShaderInfoLog(s, 1024, nullptr, log);
    std::cerr << label << " compilation failed:\n"
              << log << "\n";
}

Mesh::Mesh()
{
    float vertices[] = {
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.9f,
        0.0f,
        0.9f,
        0.0f,
        0.0f,
    };

    const char *vertexShaderSource = R"(
        #version 460 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 uModel;
        void main() { gl_Position = uModel * vec4(aPos, 1.0); }
    )";

    const char *fragmentShaderSource = R"(
        #version 460 core
        out vec4 FragColor;
        void main() { FragColor = vec4(0.54, 0.69, 0.79, 1.0); }
    )";

    // Create and compile shaders

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader, "VERTEX SHADER");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader, "FRAGMENT SHADER");

    // Create and compile program

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Mesh::draw()
{
    glUseProgram(program);

    GLint loc = glGetUniformLocation(program, "uModel");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform.getMatrix()));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}