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
	float4x4 mat;
	float4x4 normalMat;
};

cbuffer LightConstantBuffer : register(b1)
{
	float4 cameraPosition;
	float4 lightDirection;
	float4 colorIntencity;
};

cbuffer MaterialConstantBuffer : register(b2)
{
	float ambientCoef;
	float difuseCoef;
	float specularAbsorptionCoef;
	float specularShininessCoef;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(input.pos, mat);
	//output.pos = input.pos;
	output.normal = input.normal;
	output.textureCoordinate = input.textureCoordinate;

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float3 normal = normalize(mul(input.normal.xyz, mat));
	float3 lightBackward = normalize(-lightDirection.xyz);
	float3 lightForward = normalize(lightDirection.xyz);
	float3 toCamera = normalize(cameraPosition.xyz - input.pos.xyz);
	float3 lightReflect = normalize(reflect(lightForward, normal));
	float4 setPixelColor = objTexture.Sample(objSamplerState, input.textureCoordinate);

	float3 diffuse = max(0.0, dot(lightBackward, normal)) * difuseCoef;

	float3 specular = specularAbsorptionCoef * pow(max(0.0, dot(-lightReflect, toCamera)), specularShininessCoef);
	float3 lighting = colorIntencity * (diffuse + specular + ambientCoef);

	return float4(lighting, 1) * setPixelColor;
}

