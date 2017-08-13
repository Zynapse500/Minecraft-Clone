//
// Created by chris on 11/08/2017.
//

#include <iostream>
#include "Shader.h"

Shader::Shader(const char **sources, GLuint *types, int count) {
    create(sources, types, count);
}

void Shader::create(const char **sources, GLuint *types, int count) {
    auto shaders = new GLuint[count];
    this->program = glCreateProgram();

    // Compile shaders
    for (int i = 0; i < count; ++i) {
        shaders[i] = compileShader(sources[i], types[i]);
        glAttachShader(this->program, shaders[i]);
    }

    glLinkProgram(program);

    // Check for link errors
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(success == 0)
    {
        std::cout << "Error: Failed to link shader program" << std::endl;
        int logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        auto infoLog = new char[logLength];
        glGetProgramInfoLog(program, logLength, &logLength, infoLog);

        std::cout << infoLog << std::endl;

        throw std::runtime_error(infoLog);
    }

    registerAllUniforms();

    for (int i = 0; i < count; ++i) {
        glDeleteShader(shaders[i]);
    }
}

GLuint Shader::compileShader(const char *source, GLuint type) {
    if(source == nullptr)
        throw std::runtime_error("ERROR: Shader source was null!");

    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

void Shader::use() {
    glUseProgram(this->program);
}

GLint Shader::getUniformLocation(const char *name) {
    return uniformLocations[name];
}

void Shader::registerAllUniforms() {
    int uniformCount;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

    auto lengths = new GLint[uniformCount];
    auto indices = new GLuint[uniformCount];
    for(GLuint i = 0; i < uniformCount; i++) {
        indices[i] = i;
    }
    glGetActiveUniformsiv(program, uniformCount, indices, GL_UNIFORM_NAME_LENGTH, lengths);

    for(GLuint i = 0; i < uniformCount; i++) {
        int length = lengths[i];
        auto name = new char[length];
        glGetActiveUniformName(program, i, length, &length, name);

        uniformLocations[name] = glGetUniformLocation(program, name);
    }
}
