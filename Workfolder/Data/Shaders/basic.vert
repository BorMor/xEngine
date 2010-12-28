#version 330		

#include "common.vert"

layout(location = ATTR_POSITION) in vec4 position;

uniform mat4 worldViewProj;
uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

void main(void)
{
	vec4 pos = vec4(position.x, position.z, position.y, 1.f);
	//gl_Position = pos * worldViewProj;
	gl_Position = pos * world * view * proj;
	//gl_Position = proj * view * world * pos;
	//gl_Position = pos * worldViewProj;
}