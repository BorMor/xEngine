Texture2D diffuseMap;

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
	float3 Normal  : NORMAL;
	float3 LightDir : TEXCOORD1;
};

float4 main(PS_INPUT input) : SV_Target
{
	float4 result = float4(0.0, 0.0, 0.0, 1.0);
	float4 diffuse = diffuseMap.Sample(samLinear, input.TexCoord);

	float3 N = normalize(input.Normal);
	float3 L = normalize(input.LightDir);	

	float lambertTerm = dot(N,L);
	if(lambertTerm > 0.0)
		result += float4(0.9, 0.9, 0.9, 1.0) * diffuse * lambertTerm;	

	return result;
}