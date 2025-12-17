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

    void rotate(const float radians, const glm::vec3 &axis)
    {
        matrix_ = glm::rotate(matrix_, radians, axis);
    }

private:
    glm::mat4 matrix_;
};