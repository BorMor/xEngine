#version 330		

#include "common.vert"

layout(location = ATTR_POSITION) in vec4 position;

void main(void)
{
	gl_Position.x = position.x;
	gl_Position.y = position.z - 0.9f;
	gl_Position.z = position.y;
}