#include "../include/Camera.hpp"
#include <iostream>

Camera::Camera(glm::vec3 pos)
{
    setPosition(pos);

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
    dirty = true;
}

void Camera::setFOV(float fieldOfView)
{
    fov = fieldOfView;
    dirty = true;
}

void Camera::setAspectRatio(float ratio)
{
    aspectRatio = ratio;
    dirty = true;
}

void Camera::setNearPlane(float newNearPlane)
{
    nearPlane = newNearPlane;
    dirty = true;
}

void Camera::setFarPlane(float newFarPlane)
{
    farPlane = newFarPlane;
    dirty = true;
}

glm::vec3 Camera::getPosition() const
{
    return position;
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
    glm::vec3 forward = glm::normalize(glm::vec3{target.x - position.x, 1.0f, target.z - position.z});
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::vec3 worldDisplacement = (right * translation.x +
                                   up * translation.y +
                                   forward * translation.z);

    position += worldDisplacement;
    target += worldDisplacement;
    dirty = true;
}

void Camera::rotate(glm::vec3 axis, float angle)
{
    glm::vec3 direction = target - position;

    std::cout << "x: " << direction.x << " y:" << direction.y << " z: " << direction.z << std::endl;
    if (target.z >= position.z && glm::normalize(axis).x != 0.f)
    {
        axis.x = -axis.x;
    }
    glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

    glm::quat rotation = deltaRotation;
    rotation = glm::normalize(rotation);

    glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    target = position + newDirection;
    dirty = true;
}

glm::mat4 &Camera::getProjectionMatrix()
{
    if (dirty)
    {
        updateMatrices();
        dirty = false;
    }
    return projectionMatrix;
}

glm::mat4 &Camera::getViewMatrix()
{
    if (dirty)
    {
        updateMatrices();
        dirty = false;
    }
    return viewMatrix;
}

void Camera::updateMatrices()
{

    viewMatrix = glm::lookAt(position, target, up);
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}