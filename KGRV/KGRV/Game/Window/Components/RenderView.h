#pragma once
#include "../GameWindow.h"
#include "GameWindowComponent.h"
#include "../../Graphics/RenderObject.h"
#include "../../GameHandle.h"
#include <d3d.h>
#include <d3d11.h>
#include <wrl.h>
#include <vector>
class GameHandle;
class RenderView: public GameWindowComponent
{
public:
	RenderView(GameWindow* targetWindow, GameHandle* game) : GameWindowComponent(targetWindow) {
		this->game = game;
	}

	HRESULT Initalize() override;
	void UpdateComponentView() override;
	void AddRenderObject(RenderObject* object);
	void RemoveRenderObject(RenderObject* object);
	GameHandle* game;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* backTex;
	ID3D11RasterizerState* rastState;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
private:
	std::vector<RenderObject*> renderObjects;
};

