float4 main(float4 Pos : POSITION) : SV_POSITION
{
	return float4(Pos.x, Pos.z - 0.9f, Pos.y, 1.f);
}