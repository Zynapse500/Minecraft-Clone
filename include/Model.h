//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_MODEL_H
#define MINECRAFT_CLONE_MODEL_H


#include <GL/glew.h>
#include <Batch/glm.h>

struct Vertex
{
    glm::vec3 position = glm::vec3(0);
    glm::vec2 texCoord = glm::vec2(0);
    glm::vec3 normal = glm::vec3(0);

    Vertex(glm::vec3 position) {
        this->position = position;
    }

    Vertex(glm::vec3 position, glm::vec2 texCoord) {
        this->position = position;
        this->texCoord = texCoord;
    }

    Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal) {
        this->position = position;
        this->texCoord = texCoord;
        this->normal = normal;
    }

};


class Model {
public:

    // Initializes the model's vao
    Model();

    // Destroys all OpenGL instances
    ~Model();

    // Renders the model
    void draw();
    void draw(GLenum mode);

    // Sets the vertices of the model
    void setVertices(Vertex* vertices, GLuint count);

    void setIndices(GLuint *indices, GLuint count);

private:

    // Handle to vao, vbo and index buffer
    GLuint h_vao = 0;
    GLuint h_vbo = 0;
    GLuint h_indexBuffer = 0;

    // Number of vertices and indices in model
    GLuint vertexCount = 0;
    GLuint indexCount = 0;

};


#endif //MINECRAFT_CLONE_MODEL_H
