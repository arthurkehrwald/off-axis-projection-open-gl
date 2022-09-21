#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;

out vec4 FragColor;

uniform sampler2D DiffuseTexture;
uniform vec4 TintColor;

void main() 
{
	FragColor = texture(DiffuseTexture, TexCoords) * TintColor;
	FragColor.a = TintColor.a;
}