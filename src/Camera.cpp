#include "../include/Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 targ, glm::vec3 upVec)
{
    setTarget(targ);
    setPosition(pos);
    setUpVec(upVec);

    float aspRatio = 4.0f / 3.0f;
    setFOV(45.f);
    setAspectRatio(aspRatio);
    setNearPlane(1.f);
    setFarPlane(100.f);

    updateMatrices();
}

void Camera::setPosition(glm::vec3 newPosition)
{
    position = newPosition;
}

void Camera::setTarget(glm::vec3 newTarget)
{
    target = newTarget;
}

void Camera::setUpVec(glm::vec3 upVec)
{
    up = upVec;
}

void Camera::setFOV(float fieldOfView)
{
    fov = fieldOfView;
}

void Camera::setAspectRatio(float ratio)
{
    aspectRatio = ratio;
}

void Camera::setNearPlane(float newNearPlane)
{
    nearPlane = newNearPlane;
}

void Camera::setFarPlane(float newFarPlane)
{
    farPlane = newFarPlane;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getTarget() const
{
    return target;
}

glm::vec3 Camera::getUpVec() const
{
    return up;
}

float Camera::getFOV() const
{
    return fov;
}

float Camera::getAspectRatio() const
{
    return aspectRatio;
}

float Camera::getNearPlane() const
{
    return nearPlane;
}

float Camera::getFarPlane() const
{
    return farPlane;
}

void Camera::translate(glm::vec3 translation)
{
    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::vec3 worldDisplacement = (right * translation.x) +
                                  (up * translation.y) +
                                  (forward * translation.z);

    position += worldDisplacement;
    target += worldDisplacement;
}

void Camera::rotate(glm::vec3 axis, float angle)
{
    glm::vec3 direction = target - position;

    glm::mat4 rotation = glm::rotate(
        glm::mat4(1.0f),
        glm::radians(angle),
        glm::normalize(axis));

    glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));

    target = position + newDirection;
}

glm::mat4 &Camera::getProjectionMatrix()
{
    updateMatrices();
    return projectionMatrix;
}

glm::mat4 &Camera::getViewMatrix()
{
    updateMatrices();
    return viewMatrix;
}

void Camera::updateMatrices()
{
    viewMatrix = glm::lookAt(position, target, up);
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}