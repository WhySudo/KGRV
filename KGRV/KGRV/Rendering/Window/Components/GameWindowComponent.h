#pragma once
#include "../GameWindow.h"
#include <d3d.h>

class GameWindowComponent {
public:
	GameWindowComponent(GameWindow* targetWindow) {
		this->targetWindow = targetWindow;
	}
	virtual HRESULT Initalize() = 0;
	virtual void UpdateComponentView() = 0;
	GameWindow* targetWindow;
};