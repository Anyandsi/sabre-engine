#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aUV;
out vec2 vertUV;
uniform mat4 uModel;

void main()
{
    vertUV = aUV;
    gl_Position = uModel * vec4(aPos, 1.0);
}