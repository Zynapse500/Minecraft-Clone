cmake_minimum_required(VERSION 3.8)
project(Minecraft_Clone)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Og")

include_directories(include)

# OS specific settings
if(WIN32)
    set(DEPENDENCIES -lopengl32 -lglfw3)
    # Include OpenGL headers and libraries
    set(OPENGL_DIRECTORY "C:/Users/Christofer/Documents/C++/OpenGL/MinGW/OpenGL")
    if(NOT EXISTS ${OPENGL_DIRECTORY})
        set(OPENGL_DIRECTORY "D:/Programming/OpenGL - MinGW")
    endif()

    include_directories("${OPENGL_DIRECTORY}/Includes")
    link_directories("${OPENGL_DIRECTORY}/Libraries")
endif(WIN32)

if(UNIX)
    set(DEPENDENCIES -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor)
endif(UNIX)


# Set the paths to all the sourcefiles
set(SOURCE_FILES
        src/External/glew.c include/GL/glew.h
        include/IMG/lodepng.h src/External/lodepng.cpp
        include/Batch/glm.h

    # Utility
        include/ReadFile.h

    # Main
        src/main.cpp

    # GL Wrappers and misc
        src/Model.cpp include/Model.h
        src/Shader.cpp include/Shader.h
        src/Texture.cpp include/Texture.h
        src/TextureRegion.cpp include/TextureRegion.h
        src/TextureStitching.cpp include/TextureStitching.h

        src/FractalNoise.cpp include/FractalNoise.h
        src/Perlin.cpp include/Perlin.h

    # Rendering
        src/SpriteRenderer.cpp include/SpriteRenderer.h

    # Camera and controls
        include/Camera.h
        src/FirstPersonController.cpp include/FirstPersonController.h

    # World
        src/Chunk.cpp include/Chunk.h
        src/World.cpp include/World.h

    # Blocks
        src/Block.cpp include/Block.h
        src/Blocks/Grass.cpp src/Blocks/Grass.h
        src/Blocks/AggregateBlockRegister.cpp src/Blocks/AggregateBlockRegister.h
        src/Blocks/Stone.cpp src/Blocks/Stone.h
        src/Blocks/Dirt.cpp src/Blocks/Dirt.h
        src/Blocks/Air.cpp src/Blocks/Air.h

        )

add_executable(Minecraft_Clone ${SOURCE_FILES})


target_link_libraries(Minecraft_Clone ${DEPENDENCIES})






