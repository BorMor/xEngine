matrix worldView;
matrix worldViewProj;
float3 lightDir;

struct VS_INPUT
{
    float4 Position : POSITION;
	float3 Normal: NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;	
    float2 TexCoord : TEXCOORD0;
	float3 Normal : NORMAL;
	float3 LightDir : TEXCOORD1;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Position = mul(input.Position, worldViewProj);
	output.Normal = input.Normal;
	output.LightDir = mul(lightDir, worldView);
	output.TexCoord = input.TexCoord;
	return output;
}