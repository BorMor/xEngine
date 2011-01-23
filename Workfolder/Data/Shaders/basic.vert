#version 330		

#include "common.vert"

layout(location = ATTR_POSITION) in vec4 Position;
layout(location = ATTR_NORMAL) in vec3 Normal;
layout(location = ATTR_TEXCOORD) in vec2 TexCoord;

uniform mat4 worldView;
uniform mat4 worldViewProj;
uniform vec3 lightDir;

out vec2 texcoord;
out vec3 normal;
out vec4 light_dir;

void main(void)
{
	texcoord = TexCoord;// + lightDir.xy;
	normal = Normal;
	light_dir = vec4(lightDir, 1.0) * worldView;
	gl_Position = Position * worldViewProj;
}