# version 450 core

layout (location = 0) in vec3 inPosition; 
layout (location = 1) in vec2 inTextureCoord; 


out vec2 passTextureCoord; 
uniform mat4 viewProjMatrix; 


void main(){
	
	gl_Position = viewProjMatrix * vec4(inPosition, 1.0); 
	passTextureCoord = inTextureCoord; 

}