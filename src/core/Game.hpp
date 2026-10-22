#pragma once
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class Shader;
class Camera;
class UICamera;
class Renderer;

class Game
{

public:
  Game();

  ~Game();

  void run();

private:
  void initWindow();
  void initCamera();
  void setCallbacks();
  void initSettings();
  void processInput(float deltaTime);
  void loadShaders();

  void draw();
  void update();

  GLFWwindow *mWindow;
  Camera *mCamera;
  UICamera *mUi;
  Shader *mShader;
  Renderer *mRenderer;

  glm::dvec2 mMousePos{0.f, 0};

  glm::vec2 mLastMousePos{0.f, 0.f};
  glm::vec2 mAngle{0.f, 0.f};

  float mSensitivity{5.f};
};
