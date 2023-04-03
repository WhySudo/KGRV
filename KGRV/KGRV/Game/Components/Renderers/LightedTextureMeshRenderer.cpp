#include "LightedTextureMeshRenderer.h"
#include "ConstantBuffers.h"
#include "../Light/Light.h"
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
	UpdateMaterialBuffer();
	UpdateLightBuffer();
}

void LightedTextureMeshRenderer::InitBuffers(ID3D11Device* device)
{
	MeshRenderer::InitBuffers(device);
	lightBuffer = CreateLightBuffer(device);
	materialBuffer = CreateMaterialBuffer(device);
}

void LightedTextureMeshRenderer::UpdateLightBuffer()
{

	auto lightInstance = gameObject->gameHandle->loadedScene->light;
	auto cameraInstance = gameObject->gameHandle->loadedScene->currentCamera;
	LightConstantBuffer lightData = {};
	if (lightInstance != nullptr)
	{
		
		auto lightTransform = lightInstance->gameObject->transform;
		auto matrix = lightTransform->LocalToGlobalRotationMatrix();// *cameraInstance->ViewMatrix()* cameraInstance->ProjectionMatrix();
		lightData.lightDirection = (Vector4)lightTransform->forward; // XMVector3Transform(lightTransform->forward, matrix);
		Vector3 tempDir;
		//Vector3::TransformNormal((Vector3)lightData.lightDirection, matrix, tempDir);
		//lightData.lightDirection = (Vector4)tempDir;

//		auto normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, matrix));

		auto cameraTransform = cameraInstance->gameObject->transform;
		matrix = cameraTransform->LocalToGlobalMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		lightData.cameraPosition = (Vector4)cameraInstance->gameObject->transform->position;//(Vector4)XMVector3Transform(cameraInstance->gameObject->transform->position, matrix);

		lightData.colorIntencity = Vector4(0, 0, 0, 1) + (Vector4)lightInstance->ColorIntencity();

	}
	D3D11_MAPPED_SUBRESOURCE lightDataMappedResource;
	auto hr = gameObject->gameHandle->renderView->context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightDataMappedResource);
	CopyMemory(lightDataMappedResource.pData, &lightData, sizeof(LightConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(lightBuffer, 0);
}

void LightedTextureMeshRenderer::UpdateMaterialBuffer()
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
void LightedTextureMeshRenderer::DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState)
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
