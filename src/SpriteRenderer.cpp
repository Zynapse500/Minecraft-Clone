//
// Created by Christofer on 20/08/2017.
//

#include "SpriteRenderer.h"

const char *shaderSources[] = {
        ""
                "#version 330\n"
                "\n"
                "layout(location = 0) in vec3 position;\n"
                "layout(location = 1) in vec2 texCoords;\n"
                "\n"
                "uniform mat4 projectionViewMatrix = mat4(1.0);\n"
                "\n"
                "out vec2 texCoord;\n"
                "\n"
                "void main() {\n"
                "    gl_Position = projectionViewMatrix * vec4(position, 1);\n"

                "    texCoord = texCoords;\n"
                "}",
        ""
                "#version 330\n"

                "out vec4 outColor;\n"

                "uniform sampler2D tex0;\n"

                "in vec2 texCoord;\n"

                "void main() {\n"
                "   outColor = texture(tex0, texCoord);\n"
                "}\n"
};

SpriteRenderer::SpriteRenderer() {

    GLuint types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    this->shader.create(shaderSources, types, 2);
}

void SpriteRenderer::begin(const glm::mat4 &projectionViewMatrix) {
    this->projectionViewMatrix = projectionViewMatrix;
}

void SpriteRenderer::end() {
    for (auto &spritePair : sprites) {
        Sprite &sprite = spritePair.second;
        flush(sprite);
    }
}

void SpriteRenderer::flush(SpriteRenderer::Sprite &sprite) {

    sprite.texture->bind();
    this->shader.use();

    glUniformMatrix4fv(this->shader.getUniformLocation("projectionViewMatrix"), 1, 0,
                       glm::value_ptr(this->projectionViewMatrix));

    vertexBuffer.setVertices(sprite.vertices.data(), sprite.vertices.size());
    vertexBuffer.setIndices(sprite.indices.data(), sprite.indices.size());

    sprite.vertices.clear();
    sprite.indices.clear();

    vertexBuffer.draw();
}

void SpriteRenderer::draw(Texture &texture, glm::vec2 position) {
    draw(texture, position, glm::vec2(texture.getWidth(), texture.getHeight()));
}

void SpriteRenderer::draw(Texture &texture, glm::vec2 position, glm::vec2 size) {
    Sprite &currentSprite = sprites[texture];
    currentSprite.texture = &texture;

    // Position
    float x = position.x,
            y = position.y,
            w = size.x,
            h = size.y;

    // Texture coordinates
    float u = 0,
            v = 0,
            us = 1,
            vs = 1;

    GLuint startVertex = currentSprite.vertices.size();

    currentSprite.vertices.emplace_back(glm::vec3(x, y, 0), glm::vec2(u, v));
    currentSprite.vertices.emplace_back(glm::vec3(x, y + h, 0), glm::vec2(u, v + vs));
    currentSprite.vertices.emplace_back(glm::vec3(x + w, y + h, 0), glm::vec2(u + us, v + vs));
    currentSprite.vertices.emplace_back(glm::vec3(x + w, y, 0), glm::vec2(u + us, v));

    currentSprite.indices.push_back(startVertex + 0);
    currentSprite.indices.push_back(startVertex + 1);
    currentSprite.indices.push_back(startVertex + 2);
    currentSprite.indices.push_back(startVertex + 2);
    currentSprite.indices.push_back(startVertex + 3);
    currentSprite.indices.push_back(startVertex + 0);
}

void SpriteRenderer::draw(const TextureRegion& region, glm::vec2 position, glm::vec2 size) {
    Sprite &currentSprite = sprites[*region.texture];
    currentSprite.texture = region.texture;

    // Position
    float x = position.x,
            y = position.y,
            w = size.x,
            h = size.y;

    // Texture coordinates
    float u = region.offset.x,
            v = region.offset.y,
            us = region.size.x,
            vs = region.size.y;

    GLuint startVertex = currentSprite.vertices.size();

    currentSprite.vertices.emplace_back(glm::vec3(x, y, 0), glm::vec2(u, v));
    currentSprite.vertices.emplace_back(glm::vec3(x, y + h, 0), glm::vec2(u, v + vs));
    currentSprite.vertices.emplace_back(glm::vec3(x + w, y + h, 0), glm::vec2(u + us, v + vs));
    currentSprite.vertices.emplace_back(glm::vec3(x + w, y, 0), glm::vec2(u + us, v));

    currentSprite.indices.push_back(startVertex + 0);
    currentSprite.indices.push_back(startVertex + 1);
    currentSprite.indices.push_back(startVertex + 2);
    currentSprite.indices.push_back(startVertex + 2);
    currentSprite.indices.push_back(startVertex + 3);
    currentSprite.indices.push_back(startVertex + 0);
}

