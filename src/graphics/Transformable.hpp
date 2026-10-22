#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transformable
{
public:
    void translate(glm::vec3 translation)
    {
        mPosition += translation;
        mDirty = true;
    }

    void setPosition(glm::vec3 newPos)
    {
        mPosition = newPos;
        mDirty = true;
    }

    void scale(glm::vec3 scaling)
    {
        mScale += scaling;
        mDirty = true;
    }

    void setScale(glm::vec3 newScale)
    {
        mScale = newScale;
        mDirty = true;
    }

    void rotate(glm::vec3 axis, float angle)
    {
        glm::quat deltaRotation = glm::angleAxis(glm::radians(angle), glm::normalize(axis));

        mRotation = deltaRotation * mRotation;

        mRotation = glm::normalize(mRotation);
        mDirty = true;
    }

    const glm::mat4 getModelMatrix()
    {
        if (mDirty)
        {
            glm::mat4 t = glm::translate(glm::mat4{1.f}, mPosition);
            glm::mat4 r = glm::mat4_cast(mRotation);
            glm::mat4 s = glm::scale(glm::mat4{1.f}, mScale);

            mCachedModelMatrix = t * r * s;
            mDirty = false;
        }

        return mCachedModelMatrix;
    }

private:
    glm::vec3 mPosition{0.f};
    glm::vec3 mScale{1.f};
    glm::quat mRotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::mat4 mCachedModelMatrix{1.0f};

    bool mDirty{false};
};