float4 diffuse;
matrix worldViewProj;
row_major matrix world;
row_major matrix view;
row_major matrix proj;

float4 main(float4 Pos : POSITION) : SV_POSITION
{
	float4 pos = float4(Pos.x, Pos.z, Pos.y, 1.f);
	/*pos = mul(pos, world);
	pos = mul(pos, view);
	pos = mul(pos, proj);
	return pos;*/
	return mul(pos, worldViewProj);
	return mul(pos, worldViewProj);
	//return mul(pos, worldViewProj);
}