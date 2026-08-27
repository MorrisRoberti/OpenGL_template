#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos, glm::vec3 targ, glm::vec3 upVec);

    void setPosition(glm::vec3 newPosition);

    void setTarget(glm::vec3 newTarget);

    void setUpVec(glm::vec3 upVec);

    void setFOV(float fieldOfView);

    void setAspectRatio(float ratio);

    void setNearPlane(float newNearPlane);

    void setFarPlane(float newFarPlane);

    glm::vec3 getPosition() const;

    glm::vec3 getTarget() const;

    glm::vec3 getUpVec() const;

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
    glm::vec3 target;
    glm::vec3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};