#pragma once
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "assimp/material.h"
#include "../ThirdParty/WICTextureLoader.h"
#include "../ThirdParty/SimpleMath.h"
#include <DirectXMath.h>
#include <iostream>

class Texture
{
public:
	ID3D11SamplerState* samplerState;
	ID3D11ShaderResourceView* textureResourceView;
	ID3D11Texture2D* texture;

	Texture() {

	}
	void LoadFromFile(ID3D11Device* device, std::string path) {
		Initialize(device);

		std::wstring widestr = std::wstring(path.begin(), path.end());
		const wchar_t* widecstr = widestr.c_str();

		auto hr = DirectX::CreateWICTextureFromFile(device, widecstr, nullptr, &textureResourceView);

		if (FAILED(hr))
		{
			throw "FailedToLoadFromFile";
		}
		std::cout << "Loaded texture: " << path << std::endl;

	}
	void InitFromColor(ID3D11Device* device, DirectX::XMFLOAT4 color) {
		CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1);
		ID3D11Texture2D* p2DTexture = nullptr;
		D3D11_SUBRESOURCE_DATA initialData{};
		initialData.pSysMem = &color;
		initialData.SysMemPitch = 1 * sizeof(DirectX::XMFLOAT4);
		auto  hr = device->CreateTexture2D(&textureDesc, &initialData, &p2DTexture);



		if (FAILED(hr))
		{
			throw "FailedToCreate2DTexture";
		}

		texture = static_cast<ID3D11Texture2D*>(p2DTexture);
		CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);
		hr = device->CreateShaderResourceView(texture, &srvDesc, &textureResourceView);

		if (FAILED(hr))
		{
			throw "FailedToCreate2DTexture";
		}

	}

protected:
	void Initialize(ID3D11Device* device) {
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		auto hr = device->CreateSamplerState(&sampDesc, &this->samplerState); //Create sampler state
		if (FAILED(hr))
		{
			throw "FailedToCreateSampler";
		}

	}
};

