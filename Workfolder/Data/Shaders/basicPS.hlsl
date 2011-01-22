Texture2D diffuse;

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
};

float4 main(PS_INPUT input) : SV_Target
{
	return diffuse.Sample(samLinear, input.TexCoord);// + float4(1.0f, 1.0f, 1.0f, 1.0f);
}