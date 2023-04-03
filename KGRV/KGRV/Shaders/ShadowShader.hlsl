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
	float4 lightPos : TEXCOORD2;
};

cbuffer TransformConstantBuffer : register(b0)
{
	float4x4 mat;
	float4x4 normalMat;	
	float4x4 worldViewProj;	
	float4x4 cameraViewProj;
};

cbuffer LightConstantBuffer : register(b1)
{
	float4 cameraPosition;
	float4 lightDirection;
	float4 colorIntencity;
	float4x4 lightMat;
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


float IsLighted(float4 lightViewPosition, float4 pos)
{
	float4 fragPosLightSpace = lightViewPosition;
	// perform perspective divide
	float3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	//float closestDepth = depthTexture.Sample(objSamplerState, projCoords.xy).r;
	float closestDepth = GetDepth(pos);
	// get depth of current fragment from light's perspective
	float currentDepth = fragPosLightSpace.z / fragPosLightSpace.w * 0.5 + 0.5;

	return closestDepth;

	// check whether current frag pos is in shadow
	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

	return shadow;
}



PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(input.pos, mat);
	//output.pos = input.pos;
	//float4x4 normalMatrix = inverse(transpose(mat));
	//output.normal = mul(float4(input.normal.xyz, 0), normalMat);
	output.normal = mul(input.normal, normalMat);
	//output.normal = input.normal;
	output.textureCoordinate = input.textureCoordinate;
	output.lightPos = mul(output.pos, lightMat);

	return output;
}

float1 CalculateDiffuse(PS_IN input) {

	float3 normal = normalize(input.normal.xyz);
	float3 lightBackward = normalize(-lightDirection.xyz);
	float1 diffuse = difuseCoef * max(0.0, dot(lightBackward, normal));
	return diffuse;
}

float3 GetLightning(PS_IN input) {
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

float4 PSMain(PS_IN input) : SV_Target
{
	//return float4(input.normal.xyz, 1.0f);


	float4 setPixelColor = objTexture.Sample(objSamplerState, input.textureCoordinate);
	float3 lighting = GetLightning(input);
	float isLigthed = IsLighted(input.lightPos, input.pos);
	if (isLigthed) {
		return float4(lighting, 1) * setPixelColor;
	}
	else {
		return float4(0, 0, 0, 1);
	}
}

