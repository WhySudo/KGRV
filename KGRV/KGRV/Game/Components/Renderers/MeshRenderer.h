#pragma once
#include "../ObjectComponent.h"
#include "../../Graphics/Shaders/DepthShader.h"
class ObjectComponent;
class MeshRenderer : public ObjectComponent {
public:
	void Draw() override;
	void Update(float deltaTime) override;
	virtual ID3D11Buffer* CreateTransformBuffer(ID3D11Device* device);
	virtual bool Initialization() override;
	virtual void UpdateDepthBuffer();
	virtual void DrawDepthData(ID3D11DeviceContext* context, DepthShader* depthShader, ID3D11DepthStencilState* depthState) {};
	MeshRenderer(GameObject* gameObject, Mesh* renderedMesh, Shader* drawShader) :ObjectComponent(gameObject) {
		this->renderedMesh = renderedMesh;
		this->drawShader = drawShader;
	}

	void UpdateDrawBuffersData();

protected:
	ID3D11Buffer* CreateDepthConstantBuffer(ID3D11Device* device);
	


	virtual void UpdateDrawMatrix();
	virtual void InitBuffers(ID3D11Device* device);
	virtual void UpdateConstantBuffers();
	virtual void DrawObject(ID3D11DeviceContext* context, ID3D11RenderTargetView* targetView, ID3D11DepthStencilState* depthState);
	

	Mesh* renderedMesh;
	Shader* drawShader;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* transformBuffer;
	ID3D11Buffer* depthBuffer;
	bool moved = true;
};