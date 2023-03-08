#version 450 core

layout (location = 0) in vec3 position; 
layout (location = 1) in vec2 TexCoords; 

out vec2 outTexCoords;
uniform mat4 vpm; 


void main(){
	gl_Position = vpm * vec4(position, 1.0);
	outTexCoords = TexCoords; 
}