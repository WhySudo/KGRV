#include "ShadowMeshRenderer.h"
#include "ConstantBuffers.h"
#include "../CameraComponent.h"
#include "../Light/Light.h"
#include <iostream>
ID3D11Buffer* ShadowMeshRenderer::CreateTransformBuffer(ID3D11Device* device)
{

	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(TransformConstantBufferEx) + (16 - (sizeof(TransformConstantBufferEx) % 16)));
	std::cout << "ExBufferSize " << desc.ByteWidth << " " << sizeof(TransformConstantBufferEx) << std::endl;
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize constant buffer.";
	}

	return buffer;
}
void ShadowMeshRenderer::InitBuffers(ID3D11Device* device)
{
	MeshRenderer::InitBuffers(device);
	lightBuffer = CreateLightBuffer(device);
	materialBuffer = CreateMaterialBuffer(device);
}
void ShadowMeshRenderer::UpdateConstantBuffers()
{
	UpdateMaterialBuffer();
	UpdateLightBuffer();
}


ID3D11Buffer* ShadowMeshRenderer::CreateLightBuffer(ID3D11Device* device)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(LightConstantBufferEx));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize light buffer.";
	}

	return buffer;
}



void ShadowMeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState)
{
	if (renderedMesh->assignedTexture == nullptr) {
		return;
	}
	UINT strides[] = { sizeof(Vertex) };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(drawShader->layout);
	context->IASetPrimitiveTopology(renderedMesh->topology);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(drawShader->vertexShader, nullptr, 0);
	context->OMSetDepthStencilState(depthState, 0);

	auto tex = renderedMesh->assignedTexture;
	context->PSSetShaderResources(0, 1, &tex->textureResourceView);
	auto light = gameObject->gameHandle->loadedScene->light;
	if (light != nullptr) {
		context->PSSetShaderResources(1, 1, &light->textureResourceView);
	}
	context->PSSetShader(drawShader->pixelShader, nullptr, 0);

	context->VSSetConstantBuffers(0, 1, &transformBuffer);
	context->VSSetConstantBuffers(1, 1, &lightBuffer);
	context->VSSetConstantBuffers(2, 1, &materialBuffer);

	context->PSSetConstantBuffers(0, 1, &transformBuffer);
	context->PSSetConstantBuffers(1, 1, &lightBuffer);
	context->PSSetConstantBuffers(2, 1, &materialBuffer);

	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);




	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
}

void ShadowMeshRenderer::UpdateDrawMatrix()
{

	TransformConstantBufferEx data;
	auto camera = gameObject->gameHandle->loadedScene->currentCamera;
	if (camera == nullptr)
		return;

	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();


	data.matrix = modelMatrix; // * camera->ViewMatrix()* camera->ProjectionMatrix();
	data.matrix = DirectX::XMMatrixTranspose(data.matrix);

	data.worldViewProj = modelMatrix * camera->ViewMatrix() * camera->ProjectionMatrix();
	data.worldViewProj = DirectX::XMMatrixTranspose(data.worldViewProj);

	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));
	data.normalMatrix *= camera->ViewMatrix() * camera->ProjectionMatrix();


	data.normalMatrix = gameObject->transform->GlobalToLocalRotationMatrix();
	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, data.normalMatrix));
	data.normalMatrix = DirectX::XMMatrixTranspose(data.normalMatrix);

	D3D11_MAPPED_SUBRESOURCE transformMappedBufferData;
	HRESULT result = gameObject->gameHandle->renderView->context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &transformMappedBufferData);
	CopyMemory(transformMappedBufferData.pData, &data, sizeof(TransformConstantBufferEx));
	gameObject->gameHandle->renderView->context->Unmap(transformBuffer, 0);

}

void ShadowMeshRenderer::UpdateLightBuffer()
{

	auto lightInstance = gameObject->gameHandle->loadedScene->light;
	lightInstance->Update(0);
	auto cameraInstance = gameObject->gameHandle->loadedScene->currentCamera;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();
	LightConstantBufferEx lightData = {};
	if (lightInstance != nullptr)
	{



		auto lightTransform = lightInstance->gameObject->transform;
		auto lightMatrix = lightTransform->LocalToGlobalRotationMatrix();// *cameraInstance->ViewMatrix()* cameraInstance->ProjectionMatrix();
		
		
		lightData.lightDirection = (Vector4)lightTransform->DEFAULT_FORWARD_VECTOR; // XMVector3Transform(lightTransform->forward, matrix);

		Vector3 lightDirection;
		Vector3::TransformNormal((Vector3)lightData.lightDirection, lightMatrix, lightDirection);
		lightData.lightDirection = (Vector4)lightDirection;

		auto cameraTransform = cameraInstance->gameObject->transform;
		lightMatrix = cameraTransform->LocalToGlobalMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		lightData.cameraPosition = XMVector3Transform(cameraTransform->position, lightMatrix);


		lightData.colorIntencity = (Vector4)lightInstance->ColorIntencity();
		lightInstance->Update(0);
		lightData.lightMatrix = modelMatrix * lightInstance->ViewMatrix() * lightInstance->ProjectionMatrix();
		lightData.lightMatrix = DirectX::XMMatrixTranspose(lightData.lightMatrix);

	}
	D3D11_MAPPED_SUBRESOURCE lightDataMappedResource;
	auto hr = gameObject->gameHandle->renderView->context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightDataMappedResource);
	CopyMemory(lightDataMappedResource.pData, &lightData, sizeof(LightConstantBufferEx));
	gameObject->gameHandle->renderView->context->Unmap(lightBuffer, 0);
}

void ShadowMeshRenderer::DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState)
{
	UINT strides[] = { sizeof(Vertex) };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(depthShader->layout);
	context->IASetPrimitiveTopology(renderedMesh->topology);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(depthShader->vertexShader, nullptr, 0);
	context->PSSetShader(depthShader->pixelShader, nullptr, 0);
	context->VSSetConstantBuffers(0, 1, &depthBuffer);
	context->PSSetConstantBuffers(0, 1, &depthBuffer);
	context->OMSetDepthStencilState(depthState, 0);
	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
}
void ShadowMeshRenderer::UpdateMaterialBuffer()
{
	MaterialConstantBuffer materialData = {};
	materialData.ambientCoef = phongMaterialData.ambient;
	materialData.difuseCoef = phongMaterialData.difuse;
	materialData.specularAbsorptionCoef = phongMaterialData.specularAbsorption;
	materialData.specularShininessCoef = phongMaterialData.specularShininess;

	D3D11_MAPPED_SUBRESOURCE materialDataMappedResourse;
	HRESULT hr = gameObject->gameHandle->renderView->context->Map(materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &materialDataMappedResourse);
	CopyMemory(materialDataMappedResourse.pData, &materialData, sizeof(MaterialConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(materialBuffer, 0);
}

ID3D11Buffer* ShadowMeshRenderer::CreateMaterialBuffer(ID3D11Device* device)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(MaterialConstantBuffer));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize material buffer.";
	}
	return buffer;

}