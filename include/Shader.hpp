#pragma once
#include <glm/mat4x4.hpp>
#include <string>

class Shader
{

public:
    Shader() = delete;

    Shader(std::string vertexFilePath, std::string fragmentFilePath);

    void use();

    void setMat4(const std::string &uniformName, const glm::mat4 &matrix);

    void setUniform1i(const std::string &uniformName, int value);

private:
    unsigned int vertexShaderId;
    unsigned int fragmentShaderId;
    unsigned int programId;
};