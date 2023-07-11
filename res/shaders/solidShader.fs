#version 450 core


in vec2 passTexCoords; 
in vec3 passNormal;
in vec3 passFragPos;

out vec4 color; 

uniform sampler2D Texture; 

uniform vec3 ambientColor;
uniform float ambientLightIntensity;

uniform vec3 sunLightDirection;	
uniform vec3 sunLightColor;
uniform float sunLightIntensity;

void main()
{
	vec4 ambientLight = vec4(ambientColor, 1.0f) * ambientLightIntensity;

	vec3 norm = normalize(passNormal);
	vec3 lightDir = normalize(-sunLightDirection);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec4 diffuseLight = vec4(sunLightColor, 1.0f) * diff * sunLightIntensity;

	vec4 textureColor = texture(Texture, passTexCoords);

	color = textureColor * (ambientLight + diffuseLight);  
}
