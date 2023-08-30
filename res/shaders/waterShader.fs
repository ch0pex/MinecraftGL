#version 450 core 

in vec2 passTexCoords;
in vec3 passNormal;

out vec4 color;

uniform sampler2D Texture;
uniform float opacity;

void main()
{
	color = vec4(1.0, 1.0, 1.0, opacity) * texture(Texture, passTexCoords);
}
