#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
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

    glm::mat4 &getProjectionMatrix();

    glm::mat4 &getViewMatrix();

    void updateMatrices();

private:
    glm::vec3 position;

    glm::quat orientation;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    bool dirty{false};
};