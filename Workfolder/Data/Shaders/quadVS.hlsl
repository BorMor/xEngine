struct VS_INPUT
{
    float4 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Position = float4(input.Position.x, input.Position.y, input.Position.z, 1.f);
	output.TexCoord = input.TexCoord;
	return output;
}