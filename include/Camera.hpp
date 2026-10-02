#pragma once
#include "./Viewable.hpp"
#include <glm/vec3.hpp>

class Camera : public Viewable
{
public:
    Camera(glm::vec3 pos);

    void setPosition(glm::vec3 newPosition);

    void setFOV(float fieldOfView);

    void setAspectRatio(float ratio);

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

    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 target{0.f, 0.f, 8.f};
    glm::vec3 up{0.f, 1.f, 0.f};

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    bool dirty{false};
};