#include "MeshRenderer.h"
#include "../CameraComponent.h"
#include "../Light/Light.h"
#include <iostream>
#include "ConstantBuffers.h"
void MeshRenderer::Draw()
{
	DrawObject(
		gameObject->gameHandle->renderView->context, 
		gameObject->gameHandle->renderView->renderTargetView,
		gameObject->gameHandle->renderView->depthStencilState);
}

void MeshRenderer::Update(float deltaTime)
{
	UpdateDrawBuffersData();
}

void MeshRenderer::UpdateDrawBuffersData()
{
	UpdateDrawMatrix();
	UpdateDepthBuffer();
	UpdateConstantBuffers();
}

ID3D11Buffer* MeshRenderer::CreateDepthConstantBuffer(ID3D11Device* device)
{

	ID3D11Buffer* buffer;

	//Initialize Constant Buffer(s)
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(DepthConstantBuffer) + (16 - (sizeof(DepthConstantBuffer) % 16)));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize depth constant buffer.";
	}
	return buffer;
	//DepthConstantBuffer
}

void MeshRenderer::UpdateDrawMatrix() {
	TransformConstantBuffer data;
	auto camera = gameObject->gameHandle->loadedScene->currentCamera;
	if (camera == nullptr)
		return;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();
	data.matrix = modelMatrix * camera->ViewMatrix() * camera->ProjectionMatrix();
	data.matrix = DirectX::XMMatrixTranspose(data.matrix);
	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, data.matrix));
	data.normalMatrix = DirectX::XMMatrixTranspose(data.normalMatrix);

	//data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));
	//data.normalMatrix *= camera->ViewMatrix() * camera->ProjectionMatrix();

	data.normalMatrix = gameObject->transform->LocalToGlobalRotationMatrix();
	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, data.normalMatrix));
	data.normalMatrix = DirectX::XMMatrixTranspose(data.normalMatrix);


	D3D11_MAPPED_SUBRESOURCE transformMappedBufferData;
	HRESULT result = gameObject->gameHandle->renderView->context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &transformMappedBufferData);
	CopyMemory(transformMappedBufferData.pData, &data, sizeof(TransformConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(transformBuffer, 0);

}

void MeshRenderer::InitBuffers(ID3D11Device* device)
{
	transformBuffer = CreateTransformBuffer(device);
	depthBuffer = CreateDepthConstantBuffer(device);
}

void MeshRenderer::UpdateConstantBuffers()
{
	
}

ID3D11Buffer* MeshRenderer::CreateTransformBuffer(ID3D11Device* device) {

	ID3D11Buffer* buffer;

	//Initialize Constant Buffer(s)
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(TransformConstantBuffer) + (16 - (sizeof(TransformConstantBuffer) % 16)));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		//ErrorLogger::Log(hr, "Failed to initialize constant buffer.");
		throw "Failed to initialize constant buffer.";
	}

	return buffer;
}


bool MeshRenderer::Initialization()
{
	ID3D11Device* device = gameObject->gameHandle->renderView->device.Get();
	cout << "Try to init " << renderedMesh->initialized << renderedMesh->textured << endl;
	device->CreateBuffer(&renderedMesh->vertexBufDesc, &renderedMesh->vertexData, &vertexBuffer);
	device->CreateBuffer(&renderedMesh->indexBufDesc, &renderedMesh->indexData, &indexBuffer);



	//device->CreateDepthStencilState(&dsDesc, &pDSState);
	InitBuffers(device);
	drawShader->Initalize(device);
	return true;
}
void MeshRenderer::UpdateDepthBuffer()
{
	auto lightCamera = gameObject->gameHandle->loadedScene->light;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();
	DepthConstantBuffer depthData = {};
	if (lightCamera != nullptr) {
		depthData.worldViewProj = modelMatrix * lightCamera->ViewMatrix() * lightCamera->ProjectionMatrix();
		depthData.worldViewProj = DirectX::XMMatrixTranspose(depthData.worldViewProj);
	}
	D3D11_MAPPED_SUBRESOURCE depthMappedResource;
	HRESULT hr = gameObject->gameHandle->renderView->context->Map(depthBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &depthMappedResource);
	CopyMemory(depthMappedResource.pData, &depthData, sizeof(DepthConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(depthBuffer, 0);
}
void MeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState)
{


	UINT strides[] = { 32 };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(drawShader->layout);
	context->IASetPrimitiveTopology(renderedMesh->topology);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(drawShader->vertexShader, nullptr, 0);
	context->PSSetShader(drawShader->pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, &transformBuffer);
	context->OMSetDepthStencilState(depthState, 0);
	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);

}
