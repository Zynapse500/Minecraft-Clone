//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_SHADER_H
#define MINECRAFT_CLONE_SHADER_H

#include <GL/glew.h>

class Shader {

public:

    Shader(){}

    // Creates a shader from sources
    Shader(const char** sources, GLuint* types, int count);

    // Creates a shader from sources
    void create(const char** sources, GLuint* types, int count);

    // Use the this shader in the rendering context
    void use();

private:

    // Compiles a shader and returns it's handle
    GLuint compileShader(const char *source, GLuint type);

    // Handle to shader program
    GLuint program;

};


#endif //MINECRAFT_CLONE_SHADER_H
