#pragma once
#include "graphics/Viewable.hpp"

#include <glm/mat4x4.hpp>

class UICamera : public Viewable
{
public:
    UICamera(float left, float right, float top, float bottom, float near, float far);

    const glm::mat4 &getProjectionMatrix() override;

    const glm::mat4 &getViewMatrix() override;

private:
    float mLeft;
    float mRight;
    float mBottom;
    float mTop;
    float mZNear;
    float mZFar;

    glm::mat4 mViewMatrix{1.0f};
    glm::mat4 mProjectionMatrix;
};