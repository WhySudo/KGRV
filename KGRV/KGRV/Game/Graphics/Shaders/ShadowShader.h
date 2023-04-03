#pragma once
#include "TextureLightedShader.h"
class ShadowShader:  public TextureLightedShader
{
public:
	ShadowShader() : TextureLightedShader(L"./Shaders/ShadowShader.hlsl") {

	}
	HRESULT Initalize(ID3D11Device* device) override;
};

