#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 projectionViewMatrix = mat4(1.0);

out vec2 texCoord;

void main() {
    gl_Position = projectionViewMatrix * vec4(position, 1);

    texCoord = texCoords;
}