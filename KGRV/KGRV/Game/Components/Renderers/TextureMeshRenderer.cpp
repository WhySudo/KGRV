#include "TextureMeshRenderer.h"
#include <iostream>

void TextureMeshRenderer::DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState)
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

	context->DrawIndexed(renderedMesh->indecesCount, 0, 0);
}

void TextureMeshRenderer::DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState)
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

	/*
	gameObject->gameHandle->renderView->context->IASetInputLayout(wrapper->GetInputLayout());
	gameObject->gameHandle->renderView->context->IASetPrimitiveTopology(model->mesh->topology);
	gameObject->gameHandle->renderView->context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	gameObject->gameHandle->renderView->context->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	gameObject->gameHandle->renderView->context->VSSetShader(wrapper->GetVertexShader(), nullptr, 0);
	gameObject->gameHandle->renderView->context->RSSetState(wrapper->GetRasterizerState());
	gameObject->gameHandle->renderView->context->OMSetDepthStencilState(wrapper->GetDepthStencilState(), 0);

	//texture  >gameHandle->renderView
	gameObject->gameHandle->renderView->context->PSSetSamplers(0, 1, &model->texture->samplerState);
	gameObject->gameHandle->renderView->context->PSSetShaderResources(0, 1, &model->texture->textureResourceView);
	gameObject->gameHandle->renderView->context->PSSetShaderResources(1, 1, &gameObject->game->shadows->textureResourceView);
	gameObject->gameHandle->renderView->context->PSSetShader(wrapper->GetPixelShader(), nullptr, 0);

	gameObject->gameHandle->renderView->context->VSSetConstantBuffers(0, 1, &transformBuffer);
	gameObject->gameHandle->renderView->context->VSSetConstantBuffers(1, 1, &lightBuffer);
	gameObject->gameHandle->renderView->context->VSSetConstantBuffers(2, 1, &materialBuffer);

	gameObject->gameHandle->renderView->context->PSSetConstantBuffers(0, 1, &transformBuffer);
	gameObject->gameHandle->renderView->context->PSSetConstantBuffers(1, 1, &lightBuffer);
	gameObject->gameHandle->renderView->context->PSSetConstantBuffers(2, 1, &materialBuffer);

	gameObject->gameHandle->renderView->context->DrawIndexed(model->mesh->indexCount, 0, 0);

	*/
}
