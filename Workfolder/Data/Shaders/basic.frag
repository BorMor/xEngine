#version 330

uniform sampler2D diffuse;

in vert
{
	vec2 TexCoord;
} Vert;
									
out vec4 fragColor;

void main(void)
{
	fragColor = texture(diffuse, Vert.TexCoord);
}
