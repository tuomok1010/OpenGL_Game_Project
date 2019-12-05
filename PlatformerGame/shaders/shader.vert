#version 330 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(vPos, 0.0f, 1.0f);
	TexCoord = texCoord;
}