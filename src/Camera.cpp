#include "Camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, const glm::vec3 &target): 
position_(position), up_(up), target_(target)
{
    direction_ = glm::normalize(position_ - target_);
    right_ = glm::normalize(glm::cross(up_, direction_));
    up_ = glm::cross(direction_, right_);
}

glm::mat4 Camera::getLookAtMatrix()
{
    return glm::lookAt(position_, target_, up_);
}

void Camera::setTarget(glm::vec3 &target)
{
    target_ = target;
}

void Camera::setPosition(glm::vec3 &position)
{
    position_ = position;
}