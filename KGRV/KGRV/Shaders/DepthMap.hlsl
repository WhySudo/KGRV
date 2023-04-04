struct VS_IN
{
	float4 pos : POSITION0;
	float4 normal :NORMAL0;
	float2 textureCoordinate : TEXCOORD;
	//Vertex struct related
};

struct PS_IN
{
	float4 pos : SV_POSITION;
};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 worldViewProj;
};


PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	output.pos = mul(input.pos, worldViewProj);
	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float depth = input.pos.z / input.pos.w;
	return float4(depth, depth, depth, 1);
}

