struct VS_IN
{
	float4 pos : POSITION0;
	float4 normal :NORMAL0;
	float2 textureCoordinate : TEXCOORD;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 normal :NORMAL0;
	float2 textureCoordinate : TEXCOORD;
};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 worldViewProj;
};


PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	output.pos = mul(input.pos, worldViewProj);
	output.normal = input.normal;
	output.textureCoordinate = input.textureCoordinate;

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	//return float4(0, 1, 0, 1);
	//float depth = input.pos.w / 100;
	float depth = input.pos.z / input.pos.w * 5;
	return float4(depth, depth, depth, 1);
}

