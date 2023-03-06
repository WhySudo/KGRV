#pragma once
#include <d3d.h>
#include "Window/GameWindow.h"
#include "Window/Components/RenderView.h"
#include "Window/Components/DebugWindowText.h"
#include "Scene.h"
#include "3rdParty/Input/InputDevice.h"
class RenderView;
class Scene;
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
	Scene* loadedScene;
	InputDevice* inputDevice;
};

