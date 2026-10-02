#include "../include/UICamera.hpp"
#include <glm/ext/matrix_clip_space.hpp>

UICamera::UICamera(float l, float r, float t, float b, float near, float far)
{
    left = l;
    right = r;
    top = t;
    bottom = b;
    zNear = near;
    zFar = far;
}

const glm::mat4 &UICamera::getProjectionMatrix()
{
    projectionMatrix = glm::ortho(left, right, top, bottom, zNear, zFar);
    return projectionMatrix;
}

const glm::mat4 &UICamera::getViewMatrix()
{
    return viewMatrix;
}
