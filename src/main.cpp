#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "FirstPersonController.h"

#include "ReadFile.h"
#include "IMG/lodepng.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


struct Scene
{
    Scene() = default;

    FirstPersonController controller;

    Shader shader;
    Model model;

    Texture texture;
};


Scene* currentScene;


GLFWwindow* createWindow();
void setupCallbacks(GLFWwindow* window);

void createScene(Scene& scene);
void setupController(Scene& scene);
void createModels(Scene& scene);
void createShaders(Scene& scene);
void createTextures(Scene& scene);
void onWindowResize(GLFWwindow* window, int width, int height);


void update(Scene &scene, float deltaTime);
void render(Scene& scene);




int main() {
    std::cout << "Hello, World!" << std::endl;

    GLFWwindow* window = createWindow();

    // Enable OpenGL features
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2, 0.2, 0.2, 1.0);


    // Create scene
    Scene scene = Scene();
    createScene(scene);
    currentScene = &scene;

    // Enter main loop
    while (glfwWindowShouldClose(window) == 0)
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update(scene, 1.f/60);
        render(scene);

        glfwSwapBuffers(window);
    }


    return 0;
}


void update(Scene &scene, float deltaTime) {
    auto time = float(glfwGetTime());

    scene.controller.setPosition(2.f * glm::vec3(sinf(time), 0, cosf(time)));
    scene.controller.setDirection(glm::normalize(-scene.controller.getPosition()));
}

void render(Scene& scene)
{
    scene.texture.bind();
    scene.shader.use();

    glm::mat4 projectionViewMatrix = scene.controller.getCombinedMatrix();
    glUniformMatrix4fv(scene.shader.getUniformLocation("projectionViewMatrix"), 1, 0,
                       glm::value_ptr(projectionViewMatrix));

    scene.model.draw();
}


/*
 * Callbacks
 */

void onWindowResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    if(currentScene != nullptr)
    {
        currentScene->controller.setCameraAspect(float(width) / height);
    }
}

/*
 * SETUP
 */


GLFWwindow * createWindow() {
    if(glfwInit() == 0)
    {
        throw std::runtime_error("Failed to init GLFW!");
    }

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Clone", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(glewInit() == 1)
    {
        throw std::runtime_error("Failed to init GLEW!");
    }

    setupCallbacks(window);

    return window;
}

void setupCallbacks(GLFWwindow *window) {
    glfwSetWindowSizeCallback(window, onWindowResize);
}


void createScene(Scene &scene) {
    setupController(scene);
    createModels(scene);
    createShaders(scene);
    createTextures(scene);
}

void setupController(Scene& scene) {
    scene.controller.setCameraAspect(float(WINDOW_WIDTH) / WINDOW_HEIGHT);
}

void createModels(Scene &scene) {
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
}

void createShaders(Scene &scene) {
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
}

void createTextures(Scene &scene) {
    unsigned width = 10,
            height = 10;

    std::vector<unsigned char> pixels;
    lodepng::decode(pixels, width, height, "resources/textures/grass.png");

    scene.texture.setPixels(pixels.data(), width, height);
    scene.texture.setMinMagFilter(GL_NEAREST, GL_NEAREST);
    scene.texture.setWrapMode(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}
