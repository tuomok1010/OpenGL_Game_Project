#version 330 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 textureZoom;
uniform vec2 textureOffset;

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 0.0f, 1.0f);
	TexCoord = vec2(texCoord.x + textureOffset.x, texCoord.y + textureOffset.y) * textureZoom;
}