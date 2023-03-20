#pragma once
#include "../Shader.h"
class TextureShader: public Shader
{
public:
	TextureShader() : Shader(L"./Shaders/Texture.hlsl") {

	}
	HRESULT Initalize(ID3D11Device* device) override;
};

