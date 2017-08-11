#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ReadFile.h>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

struct Scene
{
    Scene(){}

    Shader shader;
    Model model;

    Texture texture;
};

void render(Scene& scene);
void onWindowResize(GLFWwindow* window, int width, int height);


int main() {
    std::cout << "Hello, World!" << std::endl;

    if(glfwInit() == 0)
    {
        throw std::runtime_error("Failed to init GLFW!");
    }

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Minecraft Clone", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    // Setup callbacks
    glfwSetWindowSizeCallback(window, onWindowResize);


    if(glewInit() == 1)
    {
        throw std::runtime_error("Failed to init GLEW!");
    }


    // Enable OpenGL features
    glEnable(GL_MULTISAMPLE);

    glClearColor(0.2, 0.2, 0.2, 1.0);


    // Create scene
    Scene scene = Scene();

    Vertex vertices[] = {
            Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1, 1)),
            Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)),
            Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(0, 1)),
            Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
    };

    GLuint indices[] = {
            0, 1, 3,
            3, 2, 0
    };

    scene.model.setVertices(vertices, 4);
    scene.model.setIndices(indices, 6);



    // Create shaders
    char* vertexSource = readFile("resources/shader.vert");
    char* fragmentSource = readFile("resources/shader.frag");

    const char *sources[] = {
            vertexSource,
            fragmentSource
    };
    GLuint types[] = {
            GL_VERTEX_SHADER,
            GL_FRAGMENT_SHADER
    };
    scene.shader.create(sources, types, 2);
    delete[] vertexSource;
    delete[] fragmentSource;



    // Create textures
    const int width = 10,
            height = 10;

    unsigned char pixels[width * height * 4];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = 4 * (j + i * width);

            pixels[index]     = (unsigned char)(rand() % 256);
            pixels[index + 1] = (unsigned char)(rand() % 256);
            pixels[index + 2] = (unsigned char)(rand() % 256);
            pixels[index + 3] = 255;
        }
    }

    scene.texture.setPixels(pixels, width, height);
    scene.texture.setMinMagFilter(GL_NEAREST, GL_NEAREST);
    scene.texture.setWrapMode(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);


    while (glfwWindowShouldClose(window) == 0)
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render(scene);

        glfwSwapBuffers(window);
    }


    return 0;
}


void render(Scene& scene)
{
    scene.texture.bind();
    scene.shader.use();
    scene.model.draw();
}



void onWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
