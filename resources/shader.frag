#version 330

out vec4 outColor;

uniform sampler2D tex0;

in vec2 texCoord;
in vec3 Normal;

void main() {
    vec3 normal = normalize(Normal);
	outColor = texture(tex0, texCoord); //vec4(1.0, texCoord, 1.0);

	if(normal.x < 0)
	    outColor *= 0.9;
	if(normal.x > 0)
	    outColor *= 0.75;

	if(normal.y < 0)
	    outColor *= 0.5;
	if(normal.y > 0)
	    outColor *= 1;

	if(normal.z < 0)
	    outColor *= 0.95;
	if(normal.z > 0)
	    outColor *= 0.6;
}
