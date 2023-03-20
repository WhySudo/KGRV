struct VS_IN
{
	float4 pos : POSITION0;
	float4 normal :NORMAL0;
	float2 textureCoordinate : TEXCOORD;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 textureCoordinate : TEXCOORD;
};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 mat;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(input.pos, mat);
	output.textureCoordinate = input.textureCoordinate;

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float4 col = objTexture.Sample(objSamplerState,input.textureCoordinate);
	return col;
}
