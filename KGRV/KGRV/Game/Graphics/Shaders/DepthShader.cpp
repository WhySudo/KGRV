#include "DepthShader.h"
#include <wrl.h>
#include "../../Window/GameWindow.h"
#include <iostream>
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
using namespace std;
HRESULT DepthShader::Initalize(ID3D11Device* device)
{

	this->device = device;
	HRESULT res;

	cout << "compile depth shader" << endl;
	res = D3DCompileFromFile(shaderSource,
		nullptr /*macros*/,
		nullptr /*include*/,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexBC,
		&errorVertexCode);
	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		std::cout << "ERROR COMPILE" << " " << std::endl;
		std::cout << reinterpret_cast<const char*>(errorVertexCode->GetBufferPointer()) << std::endl;
		return res;
	}
	res = D3DCompileFromFile(
		shaderSource,
		nullptr /*macros*/,
		nullptr /*include*/,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&pixelBC,
		&errorPixelCode);


	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		std::cout << "ERROR COMPILE" << std::endl;
		return res;
		/*		if (errorVertexCode) {
					char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

					std::cout << compileErrors << std::endl;
			return res;
				}
				// If there was  nothing in the error message then it simply could not find the shader file itself.
				else
				{
					return res;
		//			MessageBox(targetWindow->windowInstance, L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
				}
				return res;
			*/
	}

	device->CreateVertexShader(
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		nullptr, &vertexShader);
	device->CreatePixelShader(
		pixelBC->GetBufferPointer(),
		pixelBC->GetBufferSize(),
		nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			D3D11_INPUT_ELEMENT_DESC{
				"POSITION",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				0,
				D3D11_INPUT_PER_VERTEX_DATA,
				0 },
			D3D11_INPUT_ELEMENT_DESC{
				"TEXCOORD",
				0,
				DXGI_FORMAT_R32G32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0 },
			D3D11_INPUT_ELEMENT_DESC{
				"NORMAL",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0 }
	};

	device->CreateInputLayout(
		inputElements,
		3,
		vertexBC->GetBufferPointer(),
		vertexBC->GetBufferSize(),
		&layout);
	return res;
}
