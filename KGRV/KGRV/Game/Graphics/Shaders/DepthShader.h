#pragma once
#include "../Shader.h"
class DepthShader: public Shader
	{
	public:
		DepthShader() : Shader(L"./Shaders/DepthMap.hlsl") {

		}
		HRESULT Initalize(ID3D11Device * device) override;
};

