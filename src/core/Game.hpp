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

  GLFWwindow *window;
  Camera *camera;
  UICamera *ui;
  Shader *shader;
  Renderer *renderer;

  glm::dvec2 mousePos{0.f, 0};

  glm::vec2 lastMousePos{0.f, 0.f};
  glm::vec2 angle{0.f, 0.f};

  float sensitivity{5.f};
};
