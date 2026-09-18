#include "../include/Camera.hpp"

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
    glm::vec3 forward = orientation * glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 right = orientation * glm::vec3(1.0f, 0.0f, 0.0f);

    glm::vec3 flatForward = glm::normalize(glm::vec3{forward.x, 0.0f, forward.z});
    glm::vec3 flatRight = glm::normalize(glm::vec3{right.x, 0.0f, right.z});

    position += flatRight * translation.x;
    position += flatForward * translation.z;
    position.y += translation.y;
    dirty = true;
}

void Camera::rotate(glm::vec3 axis, float angle)
{
    glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

    orientation = orientation * deltaRotation;

    orientation = glm::normalize(orientation);
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
    glm::quat inverseRotation = glm::conjugate(orientation);

    glm::mat4 viewRotation = glm::mat4_cast(inverseRotation);

    glm::mat4 viewTranslation = glm::translate(glm::mat4(1.0f), -position);

    viewMatrix = viewRotation * viewTranslation;
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}