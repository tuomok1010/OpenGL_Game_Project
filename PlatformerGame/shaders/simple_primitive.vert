#version 330 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 0.0f, 1.0f);
	fragColor = color;
}