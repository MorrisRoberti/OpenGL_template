#pragma once
#include "./Viewable.hpp"

class UICamera : public Viewable
{
public:
    UICamera(float l, float r, float t, float b, float near, float far);

    const glm::mat4 &getProjectionMatrix() override;

    const glm::mat4 &getViewMatrix() override;

private:
    float left;
    float right;
    float bottom;
    float top;
    float zNear;
    float zFar;

    glm::mat4 viewMatrix{1.0f};
    glm::mat4 projectionMatrix;
};