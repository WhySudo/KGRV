#pragma once
#include "../Shader.h"
class TextureLightedShader : public Shader
{
public:
	TextureLightedShader() : Shader(L"./Shaders/TextureLightedShader.hlsl") {

	}
	TextureLightedShader(LPCWSTR shaderSource) : Shader(shaderSource) {

	}
	virtual HRESULT Initalize(ID3D11Device* device) override;
};


