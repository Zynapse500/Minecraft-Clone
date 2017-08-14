cmake_minimum_required(VERSION 3.8)
project(Minecraft_Clone)

set(CMAKE_CXX_STANDARD 11)


include_directories(include)

# Include OpenGL headers and libraries
set(OPENGL_DIRECTORY "D:/Programming/OpenGL - MinGW")
include_directories("${OPENGL_DIRECTORY}/Includes")
link_directories("${OPENGL_DIRECTORY}/Libraries")


# Set the paths to all the sourcefiles
set(SOURCE_FILES
        src/External/glew.c include/GL/glew.h include/IMG/lodepng.h src/External/lodepng.cpp
        src/main.cpp
        src/Model.cpp include/Model.h
        src/Shader.cpp include/Shader.h
        include/ReadFile.h
        src/Texture.cpp include/Texture.h
        include/Camera.h include/Batch/glm.h
        src/FirstPersonController.cpp include/FirstPersonController.h src/Chunk.cpp include/Chunk.h)

add_executable(Minecraft_Clone ${SOURCE_FILES})


target_link_libraries(Minecraft_Clone -lopengl32 -lglew32 -lglfw3)






