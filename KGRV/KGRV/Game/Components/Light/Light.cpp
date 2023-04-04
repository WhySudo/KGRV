#include "Light.h"
#include "../Renderers/MeshRenderer.h"
#include <iostream>
void Light::BeforeDraw()
{
	auto context = gameObject->gameHandle->renderView->context;
	context->OMSetRenderTargets(1, &lightDepthBufferRenderTargetView, depthStencilView.Get());
	//context->OMSetRenderTargets(1, &gameObject->gameHandle->renderView->renderTargetView, gameObject->gameHandle->renderView->depthStencilView.Get());

	float bgcolor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	context->ClearRenderTargetView(lightDepthBufferRenderTargetView, bgcolor);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	for (auto gameObject : gameObject->gameHandle->loadedScene->SceneObjects) {
		DrawDepthMapForObject(gameObject);
	}
	context->OMSetRenderTargets(0, nullptr, nullptr);
}

void Light::DrawDepthMapForObject(GameObject* object)
{
	if (object == gameObject) return;
	for (auto component : object->gameComponents) {
		auto renderComponent = dynamic_cast<MeshRenderer*>(component);
		if (renderComponent == nullptr) continue;

		renderComponent->DrawDepthData(gameObject->gameHandle->renderView->context, depthShader, depthStencilState);
		break;
	}


}


bool Light::Initialization()
{
	CameraComponent::Initialization();
	InitializeDepthTexture();
	return false;
}

void Light::InitializeDepthTexture() {

	std::cout << "Depth Light Initialize" << std::endl;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	auto gameHandle = gameObject->gameHandle;
	auto device = gameHandle->renderView->device;
	textureDesc.Width = static_cast<float>(depthResolution.x);
	textureDesc.Height = static_cast<float>(depthResolution.y);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	auto result = device->CreateTexture2D(&textureDesc, NULL, &lightDepthBufferTexture);
	if (FAILED(result))
		return;

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	//  render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	//  render target view.
	result = device->CreateRenderTargetView(lightDepthBufferTexture, &renderTargetViewDesc, &lightDepthBufferRenderTargetView);
	if (FAILED(result))
		return;
	//	?
	//	depthShader = game->shaderCollection->GetOrCreateTextureDepthShaderWrapper(game->device);

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R32G32B32A32_FLOAT);
	auto hr = device->CreateShaderResourceView(lightDepthBufferTexture, &srvDesc, &textureResourceView);

	//Describe our Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = static_cast<float>(depthResolution.x);
	depthStencilDesc.Height = static_cast<float>(depthResolution.y);
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = device->CreateTexture2D(&depthStencilDesc, NULL, this->depthStencilBuffer.GetAddressOf());
	if (FAILED(hr)) //If error occurred
	{
		std::cout << "error initalizing depth buffer" << std::endl;
	}

	hr = device->CreateDepthStencilView(this->depthStencilBuffer.Get(), NULL, this->depthStencilView.GetAddressOf());
	if (FAILED(hr)) //If error occurred
	{
		std::cout << "error initalizing depth buffer" << std::endl;
	}
	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	hr = device->CreateDepthStencilState(&depthstencildesc, &depthStencilState);
	if (FAILED(hr)) //If error occurred
	{
		std::cout << "error initalizing depth stencil state" << std::endl;
	}
	tex = new Texture();
	tex->Initialize(gameObject->gameHandle->renderView->device.Get());
	tex->textureResourceView = textureResourceView;
	tex->texture = lightDepthBufferTexture;
}


