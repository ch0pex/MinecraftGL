#version 450 core


in vec2 passTexCoords; 

out vec4 color; 

uniform sampler2D Texture; 


void main()
{
	color = texture(Texture, passTexCoords);
}