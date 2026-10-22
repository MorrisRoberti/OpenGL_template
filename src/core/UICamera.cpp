#include "UICamera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>

UICamera::UICamera(float left, float right, float top, float bottom, float near, float far)
{
    mLeft = left;
    mRight = right;
    mTop = top;
    mBottom = bottom;
    mZNear = near;
    mZFar = far;
}

const glm::mat4 &UICamera::getProjectionMatrix()
{
    mProjectionMatrix = glm::ortho(mLeft, mRight, mTop, mBottom, mZNear, mZFar);
    return mProjectionMatrix;
}

const glm::mat4 &UICamera::getViewMatrix()
{
    return mViewMatrix;
}
