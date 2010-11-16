#version 330		

#include "common.vert"

layout(location = ATTR_POSITION) in vec4 position;
layout(location = ATTR_DIFFUSE) in vec4 diffuse;
out vec4 color;

void main(void)
{
	gl_Position = position;
	color = diffuse;
}