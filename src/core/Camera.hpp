#pragma once
#include "Viewable.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera : public Viewable
{
public:
    Camera(glm::vec3 position);

    void setPosition(glm::vec3 newPosition);

    void setFOV(float newFov);

    void setAspectRatio(float newAspectRatio);

    void setNearPlane(float newNearPlane);

    void setFarPlane(float newFarPlane);

    glm::vec3 getPosition() const;

    float getFOV() const;

    float getAspectRatio() const;

    float getNearPlane() const;

    float getFarPlane() const;

    void translate(glm::vec3 translation);

    void rotate(glm::vec3 axis, float angle);

    const glm::mat4 &getProjectionMatrix() override;

    const glm::mat4 &getViewMatrix() override;

private:
    void updateMatrices();

    glm::vec3 mPosition{0.f, 0.f, 0.f};
    glm::vec3 mTarget{0.f, 0.f, 8.f};
    glm::vec3 mUp{0.f, 1.f, 0.f};

    float mFov;
    float mAspectRatio;
    float mNearPlane;
    float mFarPlane;

    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
    bool mDirty{false};
};