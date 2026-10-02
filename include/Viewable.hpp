#pragma once
#include <glm/mat4x4.hpp>

class Viewable
{
public:
    virtual ~Viewable() = default;
    virtual const glm::mat4 &getViewMatrix() = 0;
    virtual const glm::mat4 &getProjectionMatrix() = 0;
};