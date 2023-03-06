#include "MeshRenderer.h"
#include "CameraComponent.h"
#include <iostream>
void MeshRenderer::Draw()
{
	DrawObject(gameObject->gameHandle->renderView->context, gameObject->gameHandle->renderView->renderTargetView);
}

void MeshRenderer::Update(float deltaTime)
{
	UpdateDrawMatrix();
}

void MeshRenderer::UpdateDrawMatrix() {
	TransformConstantBuffer data;
	auto camera = gameObject->gameHandle->loadedScene->currentCamera;
	if (camera == nullptr)
		return;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->GlobalPosMatrix();
	
	//data.matrix = DirectX::XMMatrixScaling(gameObject->transform->scale.x, gameObject->transform->scale.y, gameObject->transform->scale.z) *
	//DirectX::XMMatrixTranslation(gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);
	data.matrix = modelMatrix * camera->ViewMatrix() * camera->ProjectionMatrix();
	data.matrix = DirectX::XMMatrixTranspose(data.matrix);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = gameObject->gameHandle->renderView->context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CopyMemory(mappedResource.pData, &data, sizeof(TransformConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(transformBuffer, 0);
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
	device->CreateBuffer(&renderedMesh->vertexBufDesc, &renderedMesh->vertexData, &vertexBuffer);
	device->CreateBuffer(&renderedMesh->indexBufDesc, &renderedMesh->indexData, &indexBuffer);

	//device->CreateDepthStencilState(&dsDesc, &pDSState);
	transformBuffer = CreateTransformBuffer(device);
	drawShader->Initalize(device);
	return true;
}
void MeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView)
{


	UINT strides[] = { 32 };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(drawShader->layout);
	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(drawShader->vertexShader, nullptr, 0);
	context->PSSetShader(drawShader->pixelShader, nullptr, 0);
	context->OMSetRenderTargets(1, &targetView, nullptr);
	context->VSSetConstantBuffers(0, 1, &transformBuffer);
	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
	context->OMSetRenderTargets(0, nullptr, nullptr);

}
