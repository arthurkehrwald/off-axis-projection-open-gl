#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;

void main() 
{
	FragColor = texture(DiffuseTexture, TexCoords);
}