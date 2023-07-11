#version 450 core 

in vec2 passTexCoords; 

out vec4 color;

uniform sampler2D Texture;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 0.5) * texture(Texture, passTexCoords);
}
