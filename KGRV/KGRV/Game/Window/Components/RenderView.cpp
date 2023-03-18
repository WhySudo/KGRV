#include "RenderView.h"
#include "../GameWindow.h"
#include <d3d.h>
#include <d3d11.h>

#include <iostream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")



HRESULT RenderView::Initalize(){
	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = targetWindow->width;
	swapDesc.BufferDesc.Height = targetWindow->height;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = targetWindow->windowInstance;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1; 
	swapDesc.SampleDesc.Quality = 0;

	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(res))
	{
		return res;
		// Well, that was unexpected
	}
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = device->CreateRenderTargetView(backTex, nullptr, &renderTargetView);

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = static_cast<float>(game->gameWindow->width);;
	depthStencilDesc.Height = static_cast<float>(game->gameWindow->height);;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	res = this->device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
	if (FAILED(res)) //If error occurred
	{
		return res;
		// Well, that was unexpected
	}

	res = this->device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
	if (FAILED(res)) //If error occurred
	{
		return res;
		// Well, that was unexpected
	}

	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	res = device->CreateDepthStencilState(&depthstencildesc, &depthStencilState);

	if (FAILED(res))
	{
		throw "Failed to create depth stencil state.";
	}


	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = device->CreateRasterizerState(&rastDesc, &rastState);

	context->RSSetState(rastState);


	return res;
}

void RenderView::UpdateComponentView() {
	context->ClearState();
	context->RSSetState(rastState);
	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(targetWindow->width);
	viewport.Height = static_cast<float>(targetWindow->height);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;
	float color[] = {1.0f, 0.1f, 0.1f, 1.0f };
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	context->RSSetViewports(1, &viewport);
	context->OMSetRenderTargets(1, &renderTargetView, depthStencilView.Get());
	context->ClearRenderTargetView(renderTargetView, bgcolor);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	for (auto object: game->loadedScene->SceneObjects) {
		object->Draw();
	}
	context->OMSetRenderTargets(0, nullptr, nullptr);
	
	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);


}

void RenderView::AddRenderObject(RenderObject* object) {
	renderObjects.push_back(object);
	object->Initialize(device.Get());
}
void RenderView::RemoveRenderObject(RenderObject* object) {
	//renderObjects.(object);
}