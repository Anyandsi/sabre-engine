#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
    Transform() : matrix_(1.0f) {};
    glm::mat4 getMatrix() const { return matrix_; };
    void translate(const glm::vec3 p)
    {
        matrix_ = glm::translate(matrix_, p);
    }

private:
    glm::mat4 matrix_;
};