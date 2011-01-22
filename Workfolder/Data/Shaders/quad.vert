#version 330		

#include "common.vert"

layout(location = ATTR_POSITION) in vec4 position;
layout(location = ATTR_TEXCOORD) in vec2 texcoord;

uniform mat4 worldViewProj;

out vert
{
	vec2 TexCoord;
} Vert;

void main(void)
{
	Vert.TexCoord = vec2(texcoord.x, texcoord.y);
	gl_Position = vec4(position.x, position.y, position.z, 1.f);
}