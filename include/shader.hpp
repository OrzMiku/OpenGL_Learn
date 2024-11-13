/**
 * @file shader.hpp
 * @brief OpenGL learning project shader class - compiles and links vertex and fragment shaders
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat2(const std::string &name, glm::mat2 value) const;
    void setMat3(const std::string &name, glm::mat3 value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec2(const std::string &name, glm::vec2 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setVec4(const std::string &name, glm::vec4 value) const;
};

#endif // SHADER_HPP