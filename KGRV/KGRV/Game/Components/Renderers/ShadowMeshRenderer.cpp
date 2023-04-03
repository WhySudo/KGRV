#include "ShadowMeshRenderer.h"
#include "ConstantBuffers.h"
#include "../CameraComponent.h"
#include "../Light/Light.h"
ID3D11Buffer* ShadowMeshRenderer::CreateTransformBuffer(ID3D11Device* device)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(sizeof(TransformConstantBufferEx) + (16 - (sizeof(TransformConstantBufferEx) % 16)));
	desc.StructureByteStride = 0;

	auto hr = device->CreateBuffer(&desc, 0, &buffer);
	if (FAILED(hr))
	{
		throw "Failed to initialize constant buffer.";
	}

	return buffer;
}


void ShadowMeshRenderer::UpdateDrawMatrix()
{
	TransformConstantBufferEx data;
	auto camera = gameObject->gameHandle->loadedScene->currentCamera;
	if (camera == nullptr)
		return;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();
	data.matrix = modelMatrix * camera->ViewMatrix() * camera->ProjectionMatrix();
	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, data.matrix));
	data.matrix = DirectX::XMMatrixTranspose(data.matrix);
	data.normalMatrix = DirectX::XMMatrixTranspose(data.normalMatrix);
	data.cameraViewProj = camera->ViewMatrix() * camera->ProjectionMatrix();
	data.cameraViewProj = DirectX::XMMatrixTranspose(data.cameraViewProj);
	data.normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, modelMatrix));
	data.normalMatrix *= camera->ViewMatrix() * camera->ProjectionMatrix();
	D3D11_MAPPED_SUBRESOURCE transformMappedBufferData;
	HRESULT result = gameObject->gameHandle->renderView->context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &transformMappedBufferData);
	CopyMemory(transformMappedBufferData.pData, &data, sizeof(TransformConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(transformBuffer, 0);
	//lightData.lightMatrix = modelToWorld * lightCamera->GetViewMatrix() * lightCamera->GetProjectionMatrix();
	//lightData.lightMatrix = lightMAt;
	//lightData.lightMatrix = DirectX::XMMatrixTranspose(lightData.lightMatrix);

}

void ShadowMeshRenderer::UpdateLightBuffer()
{

	auto lightInstance = gameObject->gameHandle->loadedScene->light;
	auto cameraInstance = gameObject->gameHandle->loadedScene->currentCamera;
	DirectX::XMMATRIX modelMatrix = gameObject->transform->LocalToGlobalMatrix();
	LightConstantBufferEx lightData = {};
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

		lightData.lightMatrix = modelMatrix * lightInstance->ViewMatrix() * lightInstance->ProjectionMatrix();
		lightData.lightMatrix = DirectX::XMMatrixTranspose(lightData.lightMatrix);


		/*auto lightTransform = directionLightInstance->gameObject->transform;
		auto matrix = lightTransform->LocalToGlobalRotationMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		auto normalMatrix = DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, matrix));

		lightData.lightDirection = (Vector4)XMVector3Transform(lightTransform->forward, matrix);

		auto cameraTransform = cameraInstance->gameObject->transform;
		matrix = cameraTransform->LocalToGlobalMatrix() * cameraInstance->ViewMatrix() * cameraInstance->ProjectionMatrix();
		lightData.cameraPosition = (Vector4)XMVector3Transform(cameraInstance->gameObject->transform->position, matrix);

		lightData.colorIntencity = Vector4(0, 0, 0, 1) + (Vector4)directionLightInstance->ColorIntencity();
		lightData.lightMatrix = modelMatrix * directionLightInstance->ViewMatrix() * directionLightInstance->ProjectionMatrix();
		lightData.lightMatrix = DirectX::XMMatrixTranspose(lightData.lightMatrix);*/

	}
	D3D11_MAPPED_SUBRESOURCE lightDataMappedResource;
	auto hr = gameObject->gameHandle->renderView->context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &lightDataMappedResource);
	CopyMemory(lightDataMappedResource.pData, &lightData, sizeof(LightConstantBuffer));
	gameObject->gameHandle->renderView->context->Unmap(lightBuffer, 0);
	//LightConstantBufferEx
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
