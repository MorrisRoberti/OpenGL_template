#include "Camera.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(glm::vec3 position)
{
    setPosition(position);

    float aspRatio = 4.0f / 3.0f;
    setFOV(45.f);
    setAspectRatio(aspRatio);
    setNearPlane(1.f);
    setFarPlane(100.f);
    setFarPlane(100.f);

    updateMatrices();
}

void Camera::setPosition(glm::vec3 newPosition)
{
    mPosition = newPosition;
    mDirty = true;
}

void Camera::setFOV(float newFov)
{
    mFov = newFov;
    mDirty = true;
}

void Camera::setAspectRatio(float newAspectRatio)
{
    mAspectRatio = newAspectRatio;
    mDirty = true;
}

void Camera::setNearPlane(float newNearPlane)
{
    mNearPlane = newNearPlane;
    mDirty = true;
}

void Camera::setFarPlane(float newFarPlane)
{
    mFarPlane = newFarPlane;
    mDirty = true;
}

glm::vec3 Camera::getPosition() const
{
    return mPosition;
}

float Camera::getFOV() const
{
    return mFov;
}

float Camera::getAspectRatio() const
{
    return mAspectRatio;
}

float Camera::getNearPlane() const
{
    return mNearPlane;
}

float Camera::getFarPlane() const
{
    return mFarPlane;
}

void Camera::translate(glm::vec3 translation)
{
    glm::vec3 forward = glm::normalize(glm::vec3{mTarget.x - mPosition.x, 0.0f, mTarget.z - mPosition.z});
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::vec3 worldDisplacement = (right * translation.x +
                                   up * translation.y +
                                   forward * translation.z);

    mPosition += worldDisplacement;
    mTarget += worldDisplacement;
    mDirty = true;
}

void Camera::rotate(glm::vec3 axis, float angle)
{
    glm::vec3 direction = mTarget - mPosition;

    // avoids flipping of x axis
    if (glm::normalize(axis).x != 0.f)
    {
        axis = glm::normalize(glm::cross(direction, mUp));
    }
    glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

    glm::quat rotation = deltaRotation;
    rotation = glm::normalize(rotation);

    glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    mTarget = mPosition + newDirection;
    mDirty = true;
}

const glm::mat4 &Camera::getProjectionMatrix()
{
    if (mDirty)
    {
        updateMatrices();
        mDirty = false;
    }
    return mProjectionMatrix;
}

const glm::mat4 &Camera::getViewMatrix()
{
    if (mDirty)
    {
        updateMatrices();
        mDirty = false;
    }
    return mViewMatrix;
}

void Camera::updateMatrices()
{

    mViewMatrix = glm::lookAt(mPosition, mTarget, mUp);
    mProjectionMatrix = glm::perspective(glm::radians(mFov), mAspectRatio, mNearPlane, mFarPlane);
}