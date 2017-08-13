//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_SHADER_H
#define MINECRAFT_CLONE_SHADER_H

#include <GL/glew.h>
#include <cstring>
#include <map>

class Shader {


    struct str_comp
    {
        bool operator()(const char* a, const char* b) const {
            return strcmp(a, b) < 0;
        }
    };

public:

    Shader() = default;

    // Creates a shader from sources
    Shader(const char** sources, GLuint* types, int count);

    // Creates a shader from sources
    void create(const char** sources, GLuint* types, int count);

    // Use the this shader in the rendering context
    void use();

    GLint getUniformLocation(const char *name);

private:

    // Compiles a shader and returns it's handle
    GLuint compileShader(const char *source, GLuint type);

    // Handle to shader program
    GLuint program = 0;


    // Map over all uniforms in shader
    std::map<const char*, GLint, str_comp> uniformLocations;

    // Finds all uniforms in shader and stores their names in 'uniformLocations'
    void registerAllUniforms();

};


#endif //MINECRAFT_CLONE_SHADER_H
