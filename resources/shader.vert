#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normals;

uniform mat4 projectionViewMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);

out vec2 texCoord;
out vec3 Normal;

void main() {
    gl_Position = projectionViewMatrix * modelMatrix * vec4(position, 1);

    texCoord = texCoords;
    Normal = normals;
}