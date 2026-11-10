#include "render/shader.h"
#include "utils.h"
#include <glad/gl.h>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vCode = Utils::openAndReadFile(vertexPath);
    std::string fCode = Utils::openAndReadFile(fragmentPath);

    const char* vertexCode = vCode.c_str();
    const char* fragmentCode = fCode.c_str();

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
