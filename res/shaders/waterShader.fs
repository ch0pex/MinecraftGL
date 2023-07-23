#version 450 core 

in vec2 passTexCoords; 

out vec4 color;

uniform float opacity; 
uniform sampler2D Texture;

void main()
{
	color = vec4(1.0, 1.0, 1.0, opacity) * texture(Texture, passTexCoords);
}
