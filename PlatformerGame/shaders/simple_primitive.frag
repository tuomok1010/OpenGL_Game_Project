#version 330 core

out vec4 Color;

in vec4 fragColor;

void main()
{
	Color = fragColor;
}