#version 330

uniform sampler2D diffuseMap;

in vec2 texcoord;
in vec3 normal;
in vec4 light_dir;
									
out vec4 fragColor;

void main(void)
{
	fragColor = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 diffuse = texture(diffuseMap, texcoord);
	
	vec3 N = normalize(normal);
	vec3 L = normalize(light_dir.xyz);
	
	float lambertTerm = dot(N,L);
	
	if(lambertTerm > 0.0)
		fragColor += vec4(0.9, 0.9, 0.9, 1.0) * diffuse * lambertTerm;		
}
