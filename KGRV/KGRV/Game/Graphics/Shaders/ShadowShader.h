#pragma once
#include "TextureLightedShader.h"
class ShadowShader:  public TextureLightedShader
{
public:
	ShadowShader() : TextureLightedShader(L"./Shaders/ShadowShader.hlsl") {

	}
};

