#version 330

out vec4 outColor;

uniform sampler2D tex0;

in vec2 texCoord;

void main() {
	outColor = texture(tex0, texCoord); //vec4(1.0, texCoord, 1.0);
}
