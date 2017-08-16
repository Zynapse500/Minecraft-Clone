#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Chunk.h>
#include <World.h>


#include "Shader.h"
#include "Texture.h"

#include "FirstPersonController.h"

#include "ReadFile.h"
#include "IMG/lodepng.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


struct Scene {
    Scene() = default;

    FirstPersonController controller;

    Shader shader;

    Texture texture;

//    Chunk chunk;
    World world;
};


Scene *currentScene;
GLFWwindow *window;


// Window
GLFWwindow *createWindow();

void setFullscreen(bool fullscreen);
void toggleFullscreen();



void setupCallbacks(GLFWwindow *window);

void createScene(Scene& scene);

void setupController(Scene& scene);

void createChunks(Scene& scene);

void createShaders(Scene& scene);

void createTextures(Scene& scene);

// Callbacks
void onWindowResize(GLFWwindow *window, int width, int height);

void onWindowFocused(GLFWwindow *window, int focused);

void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

// Gamestate change
void update(Scene& scene, float deltaTime);

void render(Scene& scene);


glm::vec2 mouseDelta = glm::vec2(0);

void updateMouseDelta();


int main() {
    std::cout << "Hello, World!" << std::endl;

    window = createWindow();
    setFullscreen(false);

    // Enable OpenGL features
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.2, 0.2, 0.2, 1.0);

    glEnable(GL_DEPTH_TEST);


    // Create scene
    Scene scene = Scene();
    createScene(scene);
    currentScene = &scene;


    // Main loop variables

    // Timing
    auto lastTime = float(glfwGetTime());


    // Main loop initialization
    glfwFocusWindow(window);
    onWindowFocused(window, 1);

    updateMouseDelta();
    mouseDelta.x = 0, mouseDelta.y = 0;

    // Enter main loop
    while (glfwWindowShouldClose(window) == 0) {
        // Check for input events
        glfwPollEvents();
        updateMouseDelta();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Calculate last frametime
        auto currentTime = float(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Update and render the scene
        update(scene, deltaTime);
        render(scene);


        // Swap front and back buffers
        glfwSwapBuffers(window);
    }


    return 0;
}


void update(Scene& scene, float deltaTime) {
    auto time = float(glfwGetTime());

    scene.controller.rotate(0.003f * mouseDelta.x, -0.003f * mouseDelta.y);

    float moveSpeed = 4;

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        moveSpeed *= 10;


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        scene.controller.move(FORWARD, moveSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scene.controller.move(BACKWARD, moveSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scene.controller.move(RIGHT, moveSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scene.controller.move(LEFT, moveSpeed * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        scene.controller.move(UP, moveSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        scene.controller.move(DOWN, moveSpeed * deltaTime);

    scene.world.update(scene.controller.getPosition());
}

void render(Scene& scene) {
    scene.texture.bind();
    scene.shader.use();

    glm::mat4 projectionViewMatrix = scene.controller.getCombinedMatrix();
    glUniformMatrix4fv(scene.shader.getUniformLocation("projectionViewMatrix"), 1, 0,
                       glm::value_ptr(projectionViewMatrix));

    scene.world.draw(scene.controller.getPosition());
}


/*
 * Callbacks
 */

void onWindowResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    if (currentScene != nullptr) {
        currentScene->controller.setCameraAspect(float(width) / height);
    }
}

void onWindowFocused(GLFWwindow *window, int focused) {
    if (bool(focused)) {
        std::cout << "Window gained focus!" << std::endl;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        std::cout << "Window lost focus!" << std::endl;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, 1);
                break;

            case GLFW_KEY_F1: {
                int cursorMode = glfwGetInputMode(window, GLFW_CURSOR);
                if (cursorMode != GLFW_CURSOR_NORMAL) {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                } else {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
                break;

            case GLFW_KEY_F11:
                toggleFullscreen();
                break;

            default:
                break;
        }
    }
}


/*
 * SETUP
 */


GLFWwindow *createWindow() {
    if (glfwInit() == 0) {
        throw std::runtime_error("Failed to init GLFW!");
    }

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Clone", nullptr, nullptr);
    glfwMakeContextCurrent(window);


    glfwSwapInterval(0);


    if (glewInit() == 1) {
        throw std::runtime_error("Failed to init GLEW!");
    }

    setupCallbacks(window);

    return window;
}

void setFullscreen(bool fullscreen) {
    if(fullscreen){
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        int x, y;
        glfwGetMonitorPos(monitor, &x, &y);

        glfwSetWindowMonitor(window, nullptr, x + (mode->width - WINDOW_WIDTH) / 2, y + (mode->height - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE);
    }
}

void toggleFullscreen() {
    static bool fullscreen = false;

    fullscreen = glfwGetWindowMonitor(window) == nullptr;
    setFullscreen(fullscreen);
}

void setupCallbacks(GLFWwindow *window) {
    glfwSetWindowSizeCallback(window, onWindowResize);
    glfwSetWindowFocusCallback(window, onWindowFocused);
    glfwSetKeyCallback(window, onKeyPressed);
}

void createScene(Scene& scene) {
    setupController(scene);
    createChunks(scene);
    createShaders(scene);
    createTextures(scene);
}

void setupController(Scene& scene) {
    scene.controller.setCameraAspect(float(WINDOW_WIDTH) / WINDOW_HEIGHT);
    scene.controller.setPosition(glm::vec3(0, 66, 0));
}

void createChunks(Scene& scene) {
    //scene.chunk.generate(0, 0);
    scene.world.generate();
}

void createShaders(Scene& scene) {
    char *vertexSource = readFile("resources/shader.vert");
    char *fragmentSource = readFile("resources/shader.frag");

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

void createTextures(Scene& scene) {
    unsigned width = 10,
            height = 10;

    std::vector<unsigned char> pixels;
    lodepng::decode(pixels, width, height, "resources/textures/grass.png");

    scene.texture.setPixels(pixels.data(), width, height);
    scene.texture.setMinMagFilter(GL_LINEAR, GL_NEAREST);
    scene.texture.setWrapMode(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void updateMouseDelta() {

    static double lastX = 0,
            lastY = 0;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    mouseDelta.x = float(x - lastX);
    mouseDelta.y = float(y - lastY);

    lastX = x;
    lastY = y;
}
