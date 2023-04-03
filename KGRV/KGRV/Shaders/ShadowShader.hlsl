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
	float4 worldPos :TEXCOORD3;

};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 world;
	float4x4 cameraViewProj;
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

Texture2D objTexture : TEXTURE: register(t0);
Texture2D depthMapTexture : TEXTURE: register(t1);
SamplerState objSamplerState : SAMPLER: register(s0);

float GetDepth(float4 pos) : SV_Target
{ 
	float depth = pos.z / pos.w;
	return depth;
}


float IsLighted(float4 lightViewPosition)
{
	float bias = 0.0005f;
	float isVisibleForLight = 0;
	float3 projectTexCoord;

	projectTexCoord.x = lightViewPosition.x / lightViewPosition.w;
	projectTexCoord.y = lightViewPosition.y / lightViewPosition.w;
	projectTexCoord.z = lightViewPosition.z / lightViewPosition.w;

	projectTexCoord.x = projectTexCoord.x * 0.5 + 0.5f;
	projectTexCoord.y = projectTexCoord.y * -0.5 + 0.5f;

	float max_depth = depthMapTexture.Sample(objSamplerState, projectTexCoord.xy).r;

	return max_depth;

	float currentDepth = (lightViewPosition.z / lightViewPosition.w);

	currentDepth = currentDepth - bias;

	if (max_depth >= currentDepth)
	{
		isVisibleForLight = 1;
	}
	else
	{
		isVisibleForLight = 0;
	}

	return isVisibleForLight;

}

float1 CalculateDiffuse(PS_IN input) {

	float3 normal = normalize(input.normal.xyz);
	float3 lightBackward = normalize(-lightDirection.xyz);
	float1 diffuse = difuseCoef * max(0.0, dot(lightBackward, normal));
	return diffuse;
}

float3 GetLightning(PS_IN input, float isLighted) {
	float3 normal = normalize(input.normal.xyz);
	float3 lightBackward = normalize(-lightDirection.xyz);
	float3 lightForward = normalize(lightDirection.xyz);
	float3 toCamera = normalize(cameraPosition.xyz - input.pos.xyz);
	float3 lightReflect = normalize(reflect(lightForward, normal));
	float3 diffuse = CalculateDiffuse(input);
	float3 specular = specularAbsorptionCoef * pow(max(0.0, dot(-lightReflect, toCamera)), specularShininessCoef);
	float3 lighting = colorIntencity * (diffuse + specular + ambientCoef);
	//if (isLighted < 1) {
	//	lighting = float3( 0, 0, 0 );
	//}
	return lighting;
}
float3 GetLightning_Ex(PS_IN input) {
	float3 normal = normalize(input.normal.xyz);
	float3 lightBackward = normalize(-lightDirection.xyz);
	float3 lightForward = normalize(lightDirection.xyz);
	float3 toCamera = normalize(cameraPosition.xyz - input.pos.xyz);
	float3 lightReflect = normalize(reflect(lightForward, normal));
	float3 diffuse = CalculateDiffuse(input);
	float3 specular = specularAbsorptionCoef * pow(max(0.0, dot(-lightReflect, toCamera)), specularShininessCoef);
	float3 lighting = colorIntencity * (diffuse + specular + ambientCoef);
	return lighting;
}

PS_IN VSMain(VS_IN input)
{

	PS_IN output = (PS_IN)0;

	output.pos = mul(input.pos, cameraViewProj);
	//output.pos = input.pos;
	output.worldPos = mul(input.pos, world);
	output.lightViewPosition = mul(input.pos, lightViewProj);


	//output.normal = mul(input.normal, inverse(transpose(world)));
	input.normal.w = 0;

	output.normal.w = 0;
	output.normal = mul(input.normal, normalMat);
	output.normal.w = 0;
	//output.normal = float4(normalize(cross(ddx(input.pos), ddy(input.pos))),0);

	output.textureCoordinate = input.textureCoordinate;
	return output;

}


float4 PSMain(PS_IN input) : SV_Target
{
	float4 pixelColor = objTexture.Sample(objSamplerState, input.textureCoordinate);
	float isLigthed = IsLighted(input.lightViewPosition);
	float3 lighting = GetLightning(input, isLigthed) * pixelColor;
	return float4(isLigthed, isLigthed, isLigthed, 1);
}

