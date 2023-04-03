#pragma once
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX normalMatrix;

};

struct TransformConstantBufferEx {

	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX normalMatrix;
	DirectX::XMMATRIX worldViewProj;
	DirectX::XMMATRIX cameraViewProj;
};

struct DepthConstantBuffer {
	DirectX::XMMATRIX worldViewProj;
};
struct LightConstantBuffer
{
	DirectX::SimpleMath::Vector4 cameraPosition;
	DirectX::SimpleMath::Vector4 lightDirection;
	DirectX::SimpleMath::Vector4 colorIntencity;
};

struct LightConstantBufferEx
{
	DirectX::SimpleMath::Vector4 cameraPosition;
	DirectX::SimpleMath::Vector4 lightDirection;
	DirectX::SimpleMath::Vector4 colorIntencity;
	DirectX::XMMATRIX lightMatrix;
};

struct MaterialConstantBuffer
{
	float ambientCoef;
	float difuseCoef;
	float specularAbsorptionCoef;
	float specularShininessCoef;
};

