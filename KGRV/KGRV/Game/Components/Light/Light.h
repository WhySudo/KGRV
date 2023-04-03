#pragma once
#include "../CameraComponent.h"

#include "../ObjectComponent.h"
#include "../../Graphics/Shaders/DepthShader.h"
class Light: public CameraComponent
{
public:
	Light(GameObject* obj, DepthShader* shader = nullptr) : CameraComponent(obj) {
		depthShader = shader;
	}

	void BeforeDraw() override;


	float inencity = 1.0f;
	Vector2 depthResolution = { 900.0f,  900.0f };
	XMFLOAT3 lightColor = { 1.0f, 1.0f, 1.0f };
	Vector3 ColorIntencity() {
		return lightColor * inencity;
	}
	ID3D11Texture2D* lightDepthBufferTexture;
	ID3D11RenderTargetView* lightDepthBufferRenderTargetView;
	ID3D11ShaderResourceView* textureResourceView;
	ID3D11DepthStencilState* depthStencilState;
	DepthShader* depthShader;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;

	virtual void Update(float deltaTime) override;
	virtual bool Initialization() override;
	void InitializeDepthTexture();
protected:
	void DrawDepthMapForObject(GameObject* object);
};

