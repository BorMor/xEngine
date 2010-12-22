float4 diffuse;
float2 p;

float4 main(float4 Pos : POSITION) : SV_POSITION
{
	return float4(Pos.x + p.y, Pos.z + diffuse.y - 0.9f, Pos.y, 1.f);
}