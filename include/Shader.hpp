#pragma once
#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{

public:
    Shader() = delete;

    Shader(std::string vertexFilePath, std::string fragmentFilePath);

    void use();

    void setMat4(const std::string &uniformName, glm::mat4 matrix);

    void setUniform1i(const std::string &uniformName, int value);

private:
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    GLuint programId;
};