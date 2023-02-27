#pragma once
#include <d3d11.h>
#include <wrl.h>
#include "../Window/GameWindow.h"
class Shader
{
public:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	HRESULT Initalize(ID3D11Device* device);
	Shader(LPCWSTR shaderSource);
private:
	ID3D11Device* device;
	GameWindow* targetWindow;
	LPCWSTR shaderSource;
	ID3DBlob* vertexBC = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	ID3DBlob* pixelBC;
	ID3DBlob* errorPixelCode;
};

