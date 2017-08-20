//
// Created by Christofer on 20/08/2017.
//

#ifndef MINECRAFT_CLONE_SPRITERENDERER_H
#define MINECRAFT_CLONE_SPRITERENDERER_H

#include <map>
#include <vector>

#include "Batch/glm.h"

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureRegion.h"


/*
 * Manages rendering of textures for increased performance
 */
class SpriteRenderer {

    struct Sprite {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        Texture* texture;
    };

public:


    // Initializes the renderer
    // - Compiles shader
    SpriteRenderer();


    // Prepares the renderer for rendering commands
    // Takes in the matrix used for rendering
    void begin(const glm::mat4& projectionViewMatrix);

    // Executes all the commands given since 'begin()'
    void end();


    // Renders a texture
    void draw(Texture& texture, glm::vec2 position);
    void draw(Texture& texture, glm::vec2 position, glm::vec2 size);

    // Renders a region of a texture
    void draw(TextureRegion& region, glm::vec2 position, glm::vec2 size);


private:

    // Groups sprites by texture to reduce state changes
    std::map<Texture, Sprite> sprites;


    // The shader used in rendering
    Shader shader;

    // The model used for rendering
    Model vertexBuffer;

    // Matrix used for rendering
    glm::mat4 projectionViewMatrix;


    // Renders a batch of sprites
    void flush(Sprite& sprite);
};


#endif //MINECRAFT_CLONE_SPRITERENDERER_H
