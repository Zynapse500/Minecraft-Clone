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
        include/Batch/glm.h

        include/ReadFile.h include/Camera.h

        src/main.cpp
        src/Model.cpp include/Model.h
        src/Shader.cpp include/Shader.h
        src/Texture.cpp include/Texture.h
        src/FirstPersonController.cpp include/FirstPersonController.h
        src/Chunk.cpp include/Chunk.h
        src/World.cpp include/World.h)

add_executable(Minecraft_Clone ${SOURCE_FILES})


target_link_libraries(Minecraft_Clone -lopengl32 -lglew32 -lglfw3)






