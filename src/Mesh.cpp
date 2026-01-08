#include "Mesh.h"
#include "utils/FileReader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
    // pos (x y z) + color (r g b) + uv (x y)
    float vertices[] = {
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.9f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.9f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
    };

    std::string vertexShaderSourceStr = FileReader::readFile(std::string(SHADER_DIR) + "/mesh.vert");
    const char *vertexShaderSource = vertexShaderSourceStr.c_str();

    std::string fragmentShaderSourceStr = FileReader::readFile(std::string(SHADER_DIR) + "/mesh.frag");
    const char *fragmentShaderSource = fragmentShaderSourceStr.c_str();

    // Create and compile shaders

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader, "VERTEX SHADER");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader, "FRAGMENT SHADER");

    // load texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, c;
    std::string texturePath = std::string(TEXTURE_DIR) + "/bricks.png";
    unsigned char *data = stbi_load(texturePath.c_str(), &w, &h, &c, STBI_rgb_alpha);
    if (!data)
    {
        std::cerr << "FAILED TO LOAD TEXTURE\n";
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "uTexture"), 0);

    GLint loc = glGetUniformLocation(program, "uModel");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform.getMatrix()));

    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}