#pragma once
struct TransformConstantBuffer
{
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX normalMatrix;

};
struct PhongData {
	float ambient = 0.05f;
	float difuse = 0.01f;
	float specularAbsorption = 0.5f;
	float specularShininess = 32.0f;
};
struct TransformConstantBufferEx {
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX worldViewProj;
	DirectX::XMMATRIX normalMatrix;
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

