struct VS_IN
{
	float4 pos : POSITION0;
	float4 normal :NORMAL0;
	float2 textureCoordinate : TEXCOORD;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 lightViewPosition : TEXCOORD0;
	float2 textureCoordinate : TEXCOORD1;
	float4 normal :TEXCOORD2;
};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 world;
	float4x4 normalMat;
	float4x4 worldViewProj;
};

cbuffer LightConstantBuffer : register(b1)
{
	float4 cameraPosition;
	float4 lightDirection;
	float4 colorIntencity;
	float4x4 lightViewProj;
};

cbuffer MaterialConstantBuffer : register(b2)
{
	float ambientCoef;
	float difuseCoef;
	float specularAbsorptionCoef;
	float specularShininessCoef;
};

Texture2D mainTexture : TEXTURE: register(t0);
Texture2D depthMapTexture : TEXTURE: register(t1);
SamplerState samplerState : SAMPLER: register(s0);

float IsLighted(float4 lightViewPosition)
{
	float bias = 0.0005f;
	float3 depthTexUVPos;

	depthTexUVPos = lightViewPosition.xyz / lightViewPosition.w;
	depthTexUVPos.x = depthTexUVPos.x * 0.5 + 0.5f;
	depthTexUVPos.y = depthTexUVPos.y * -0.5 + 0.5f;

	float maxLightedDepth = depthMapTexture.Sample(samplerState, depthTexUVPos.xy).r;
	float currentDepth = (lightViewPosition.z / lightViewPosition.w) - bias;

	float isLighted = ((maxLightedDepth > currentDepth) ? 1 : 0);
	
	return isLighted;

}

float1 CalculateDiffuse(PS_IN input) {

	float3 normal = normalize(input.normal.xyz);
	float3 lightBackward = normalize(-lightDirection.xyz);
	float1 diffuse = difuseCoef * max(0.0, dot(lightBackward, normal));
	return diffuse;
}

float3 CalculateSpecular(PS_IN input) {
	float3 normal = normalize(input.normal.xyz);
	float3 toCamera = normalize(cameraPosition.xyz - input.pos.xyz);
	float3 lightForward = normalize(lightDirection.xyz);
	float3 lightReflect = normalize(reflect(lightForward, normal));
	float3 specular = specularAbsorptionCoef * pow(max(0.0, dot(-lightReflect, toCamera)), specularShininessCoef);
	return specular;
}

float3 GetLightningWithShadow(PS_IN input, float isLighted) {

	float3 diffuse = CalculateDiffuse(input);
	float3 specular = CalculateSpecular(input);
	float3 lighting = (colorIntencity * isLighted * (diffuse + specular) + ambientCoef);
	return lighting;
}
float3 GetLightning_Legacy(PS_IN input) {
	float3 diffuse = CalculateDiffuse(input);
	float3 specular = CalculateSpecular(input);
	float3 lighting = colorIntencity * (diffuse + specular + ambientCoef);
	return lighting;
}

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	output.pos = mul(input.pos, worldViewProj);
	output.lightViewPosition = mul(input.pos, lightViewProj);
	input.normal.w = 0;

	output.normal.w = 0;
	output.normal = mul(input.normal, normalMat);
	output.normal.w = 0;

	output.textureCoordinate = input.textureCoordinate;
	return output;

}


float4 PSMain(PS_IN input) : SV_Target
{
	float4 pixelColor = mainTexture.Sample(samplerState, input.textureCoordinate);
	float isLigthed = IsLighted(input.lightViewPosition);
	float3 lighting = GetLightningWithShadow(input, isLigthed) * pixelColor;
	return float4(lighting, 1);
}

