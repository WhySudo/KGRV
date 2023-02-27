#pragma once
#include <d3d.h>
#include "../Rendering/Window/GameWindow.h"
#include "../Rendering/Window/Components/RenderView.h"
#include "../Rendering/Window/Components/DebugWindowText.h"
class GameHandle {
public:
	GameHandle(LPCWSTR windowName, int width, int height);
	~GameHandle();
	GameWindow* gameWindow;
	RenderView* renderView;
	DebugWindowText* debugWindowText;
	HRESULT InitializeGame();
	void ProcessGameUpdates();
	void CleanUp();
};

