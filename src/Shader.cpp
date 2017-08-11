//
// Created by chris on 11/08/2017.
//

#include <iostream>
#include "Shader.h"

Shader::Shader(const char **sources, GLuint *types, int count) {
    create(sources, types, count);
}

void Shader::create(const char **sources, GLuint *types, int count) {
    GLuint* shaders = new GLuint[count];
    this->program = glCreateProgram();
    for (int i = 0; i < count; ++i) {
        shaders[i] = compileShader(sources[i], types[i]);
        glAttachShader(this->program, shaders[i]);
    }

    glLinkProgram(program);

    // Check for link errors
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        std::cout << "Error: Failed to link shader program" << std::endl;
        int logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        char* infoLog = new char[logLength];
        glGetProgramInfoLog(program, logLength, &logLength, infoLog);

        throw std::runtime_error(infoLog);
    }



    for (int i = 0; i < count; ++i) {
        glDeleteShader(shaders[i]);
    }
}

GLuint Shader::compileShader(const char *source, GLuint type) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    return shader;
}

void Shader::use() {
    glUseProgram(this->program);
}
