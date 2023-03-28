#include "LightedTextureMeshRenderer.h"
#include "ConstantBuffers.h"
#include "../Light/DirectionLight.h"
#include "../CameraComponent.h"
void LightedTextureMeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState)
{

	UINT strides[] = { sizeof(Vertex) };
	UINT offsets[] = { 0 };
	context->IASetInputLayout(drawShader->layout);
	context->IASetPrimitiveTopology(renderedMesh->topology);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	context->VSSetShader(drawShader->vertexShader, nullptr, 0);
	context->OMSetDepthStencilState(depthState, 0);


	if (renderedMesh->assignedTexture != nullptr) {
		auto tex = renderedMesh->assignedTexture;
		context->PSSetSamplers(0, 1, &tex->samplerState);
		context->PSSetShaderResources(0, 1, &tex->textureResourceView);
	}
	context->PSSetShader(drawShader->pixelShader, nullptr, 0);

	context->VSSetConstantBuffers(0, 1, &transformBuffer);
	context->VSSetConstantBuffers(1, 1, &lightBuffer);
	context->VSSetConstantBuffers(2, 1, &materialBuffer);

	context->PSSetConstantBuffers(0, 1, &transformBuffer);
	context->PSSetConstantBuffers(1, 1, &lightBuffer);
	context->PSSetConstantBuffers(2, 1, &materialBuffer);


	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
}

void LightedTextureMeshRenderer::UpdateConstantBuffers()
{
	LightConstantBuffer lightData = {};

	MaterialConstantBuffer materialData = {};
	materialData.ambientCoef = phongMaterialData.ambient;
	materialData.difuseCoef = phongMaterialData.difuse;
	materialData.specularAbsorptionCoef = phongMaterialData.specularAbsorption;
	materialData.specularShininessCoef = phongMaterialData.specularShininess;
	auto directionLightInstance = gameObject->gameHandle->loadedScene->directionLight;
	auto cameraInstance = gameObject->gameHandle->loadedScene->currentCamera;
	if (directionLightInstance != nullptr)
	{

		auto lightTransform = directionLightInstance->gameObject->transform;
		auto matrix = lightTransform->LocalToGlobalRotationMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		auto normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, matrix));

		lightData.lightDirection = (Vector4)XMVector3Transform(lightTransform->forward, matrix);

		auto cameraTransform = cameraInstance->gameObject->transform;
		matrix = cameraTransform->LocalToGlobalMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		lightData.cameraPosition = (Vector4)XMVector3Transform(cameraInstance->gameObject->transform->position, matrix);

		lightData.colorIntencity = Vector4(0, 0, 0, 1) + (Vector4)directionLightInstance->ColorIntencity();

	}

	D3D11_MAPPED_SUBRESOURCE materialDataMappedResourse;
	HRESULT hr = gameObject->gameHandle->renderView->context->Map(materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &materialDataMappedResourse);
	CopyMemory(materialDataMappedResourse.pData, &materialData, sizeof(MaterialConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(materialBuffer, 0);

	D3D11_MAPPED_SUBRESOURCE lightDataMappedResource;
	hr = gameObject->gameHandle->renderView->context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightDataMappedResource);
	CopyMemory(lightDataMappedResource.pData, &lightData, sizeof(LightConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(lightBuffer, 0);

}

void LightedTextureMeshRenderer::InitBuffers(ID3D11Device* device)
{
	MeshRenderer::InitBuffers(device);
	lightBuffer = CreateLightBuffer(device);
	materialBuffer = CreateMaterialBuffer(device);
}

ID3D11Buffer* LightedTextureMeshRenderer::CreateLightBuffer(ID3D11Device* device)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(LightConstantBuffer));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize light buffer.";
	}

	return buffer;

}

ID3D11Buffer* LightedTextureMeshRenderer::CreateMaterialBuffer(ID3D11Device* device)
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
