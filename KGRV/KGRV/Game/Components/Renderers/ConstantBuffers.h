#pragma once
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX normalMatrix;

};
struct LightConstantBuffer
{
	DirectX::SimpleMath::Vector4 cameraPosition;
	DirectX::SimpleMath::Vector4 lightDirection;
	DirectX::SimpleMath::Vector4 colorIntencity;
};

struct MaterialConstantBuffer
{
	float ambientCoef;
	float difuseCoef;
	float specularAbsorptionCoef;
	float specularShininessCoef;
};

