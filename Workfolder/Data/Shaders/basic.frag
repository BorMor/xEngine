#version 330

uniform T
{
	vec4 diffuse;
};
									
out vec4 fragColor;

void main(void)
{
	fragColor = diffuse;
}
