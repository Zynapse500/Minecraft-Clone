//
// Created by chris on 11/08/2017.
//

#include <iostream>
#include "Model.h"

Model::Model() {
    glGenVertexArrays(1, &h_vao);
    glGenBuffers(1, &h_vbo);
    glGenBuffers(1, &h_indexBuffer);
}

void Model::draw() {
    if(this->indexCount == 0)
    {
        glBindVertexArray(h_vao);
        glBindBuffer(GL_ARRAY_BUFFER, h_vbo);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    } else {
        glBindVertexArray(h_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, h_indexBuffer);
        glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void Model::setVertices(Vertex *vertices, GLuint count) {
    this->vertexCount = count;

    glBindVertexArray(h_vao);
    glBindBuffer(GL_ARRAY_BUFFER, h_vbo);

    glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (offsetof(Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (offsetof(Vertex, texCoord)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (offsetof(Vertex, normal)));
    glBindVertexArray(0);
}

void Model::setIndices(GLuint *indices, GLuint count) {
    this->indexCount = count;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, h_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
