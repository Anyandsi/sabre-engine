#pragma once
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
    Camera(const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &target);

    glm::vec3 position_;
    glm::vec3 up_;
    glm::vec3 target_;
    glm::vec3 direction_;
    glm::vec3 right_;

    glm::mat4 getLookAtMatrix();
    void setTarget(glm::vec3 &target);
    void setPosition(glm::vec3 &position);
};