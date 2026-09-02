#pragma once
#include <glm/gtc/type_ptr.hpp>

class Transformable
{
public:
    void translate(glm::vec3 translation)
    {
        position += translation;
        dirty = true;
    }

    void setPosition(glm::vec3 newPos)
    {
        position = newPos;
        dirty = true;
    }

    void scale(glm::vec3 scaling)
    {
        mScale += scaling;
        dirty = true;
    }

    void setScale(glm::vec3 newScale)
    {
        mScale = newScale;
        dirty = true;
    }

    void rotate(glm::vec3 axis, float angle)
    {
        glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

        rotation = deltaRotation * rotation;

        rotation = glm::normalize(rotation);
        dirty = true;
    }

    const glm::mat4 getModelMatrix()
    {
        if (dirty)
        {
            glm::mat4 t = glm::translate(glm::mat4{1.f}, position);
            glm::mat4 r = glm::mat4_cast(rotation);
            glm::mat4 s = glm::scale(glm::mat4{1.f}, mScale);

            cachedModelMatrix = t * r * s;
            dirty = false;
        }

        return cachedModelMatrix;
    }

private:
    glm::vec3 position{0.f};
    glm::vec3 mScale{1.f};
    glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::mat4 cachedModelMatrix{1.0f};

    bool dirty{false};
};